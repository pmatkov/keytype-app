//---------------------------------------------------------------------------

#pragma hdrstop

#include <FireDAC.DApt.hpp>


#include "AuthenticationService.h"
#include "CryptoUtils.h"
#include "ENullPointerException.h"
#include "User.h"
#include "Logger.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

AuthenticationService::AuthenticationService(TDataModule1 *_dataModule) {

    if (_dataModule) {
       dataModule = _dataModule;
       LOGGER(LogLevel::Debug, "Created authentication service");
    }
    else {
        throw CustomExceptions::ENullPointerException();
    }
}

bool AuthenticationService::loginUser(const UnicodeString& username, const UnicodeString& password) {

	if (username.Compare("guest") == 0) {

    	user = User();
		authenticated = true;
        LOGGER(LogLevel::Info, "User <guest> signed in");

        return true;
	}

    std::unique_ptr<TFDQuery> query = std::make_unique<TFDQuery>(nullptr);
    try {

        query->Connection = dataModule->MySQLDBConnection;
        query->SQL->Text = "SELECT * FROM users WHERE username = :username";
        query->Params->ParamByName("username")->AsString = username;
        query->Open();

        if (!query->IsEmpty()) {

            query->First();
            UnicodeString hashedPassword = query->FieldByName("password")->AsString;
            UnicodeString salt = query->FieldByName("salt")->AsString;

            query->Next();

            if (!query->Eof || !verifyCredentials(hashedPassword, password + salt)) {
            	query->Close();
            	LOGGER(LogLevel::Debug, "Login failed");
            	return false;
            }

            if (!user.getUsername().IsEmpty() && user.getUsername() != username) {
                userChanged = true;
            }

            user = User(username);
            authenticated = true;

            query->Close();

            LOGGER(LogLevel::Info, "User <" + username + "> signed in");
            return true;
        }
        else {
            query->Close();

            LOGGER(LogLevel::Debug, "Login failed");
            return false;
        }
    } catch (Exception &ex) {
    	LOGGER(LogLevel::Fatal, ex.Message);
    }

    return false;
}

bool  AuthenticationService::logoutUser() {

	if (authenticated) {

        user = User();
		authenticated = false;
        LOGGER(LogLevel::Info, "User signed out");

		return true;
	}

    return false;
}

bool AuthenticationService::registerUser(const UnicodeString& username, const UnicodeString& password) {


    std::unique_ptr<TFDQuery> query = std::make_unique<TFDQuery>(nullptr);
    try {
        query->Connection = dataModule->MySQLDBConnection;
        query->SQL->Text = "SELECT * FROM users WHERE username = :username";
        query->Params->ParamByName("username")->AsString = username;
        query->Open();

        if (query->IsEmpty()) {

            UnicodeString salt = CryptoUtils::generateRandomSalt(32);
            UnicodeString hashedPassword = CryptoUtils::generateSHA512Hash(password + salt);

            query->Close();
            query->SQL->Text = "INSERT INTO users (username, password, salt) VALUES (:username, :password, :salt)";
            query->Params->ParamByName("username")->AsString = username;
            query->Params->ParamByName("password")->AsString = hashedPassword;
            query->Params->ParamByName("salt")->AsString = salt;
        	query->ExecSQL();

            if (query->RowsAffected > 0) {

                if (!user.getUsername().IsEmpty() && user.getUsername() != username) {
                    userChanged = true;
                }

            	user = User(username);
				authenticated = true;

                query->Close();

                LOGGER(LogLevel::Info, "User <" + username + "> registered");
                return true;
            }
            else {
            	LOGGER(LogLevel::Debug, "Registration failed");
                query->Close();

        		return false;
            }

        } else {
        	query->Close();

            if (OnUsernameUnavailable) {
            	LOGGER(LogLevel::Debug, "Registration failed. Username not available");
                OnUsernameUnavailable();
             }
             return false;
        }

    } catch (Exception &ex) {
    	LOGGER(LogLevel::Fatal, ex.Message);
    }

    return false;

}

const User& AuthenticationService::getUser() const {
	return user;
}


bool AuthenticationService::getUserChanged() const {
     return userChanged;
}

void AuthenticationService::setUserChanged(bool _userChanged) {
    userChanged = _userChanged;
}


bool AuthenticationService::verifyCredentials(const UnicodeString& hashedPassword, const UnicodeString& saltedPassword) {

    return CryptoUtils::generateSHA512Hash(saltedPassword) == hashedPassword;
}


