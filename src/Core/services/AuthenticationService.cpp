//---------------------------------------------------------------------------

#pragma hdrstop

#include <FireDAC.DApt.hpp>

#include "AuthenticationService.h"
#include "TextUtils.h"
#include "FileUtils.h"
#include "CryptoUtils.h"
#include "ENullPointerException.h"
#include "User.h"
#include "Logger.h"
#include "Random.h"

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

bool AuthenticationService::loginUser(const UnicodeString &username, const UnicodeString &password) {

	if (username.Compare("guest") == 0) {

        // create token for REST service

		UnicodeString token = CryptoUtils::createToken(FileUtils::createProjectSubDirPath("Keys") + "prv_key.bin", "guest", "guest");
    	user = User("guest", token);
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
            UnicodeString role = query->FieldByName("role")->AsString;

            query->Next();

            // verify credentials

            if (!query->Eof || !verifyCredentials(username, hashedPassword, password)) {
            	query->Close();
            	LOGGER(LogLevel::Debug, "Login failed");
            	return false;
            }

            if (user.getUsername() != username) {
                userChanged = true;
            }

            // create token for REST service

			UnicodeString token = CryptoUtils::createToken(FileUtils::createProjectSubDirPath("Keys") + "prv_key.bin", username, role);
            user = User(username, token);
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


bool AuthenticationService::registerUser(const UnicodeString &username, const UnicodeString &password) {


    std::unique_ptr<TFDQuery> query = std::make_unique<TFDQuery>(nullptr);
    try {
        query->Connection = dataModule->MySQLDBConnection;
        query->SQL->Text = "SELECT * FROM users WHERE username = :username";
        query->Params->ParamByName("username")->AsString = username;
        query->Open();

        if (query->IsEmpty()) {

            // generate password hash

        	UnicodeString salt = CryptoUtils::generateSalt(username);
            UnicodeString hashedSalt = CryptoUtils::generateSHA256Hash(salt);
            UnicodeString hashedPassword = CryptoUtils::generateSHA512Hash(IntToStr(Random::getRandom(1, 100)) + password + hashedSalt);

            query->Close();

            query->SQL->Text = "INSERT INTO users (username, password, role) VALUES (:username, :password, :role)";
            query->Params->ParamByName("username")->AsString = username;
            query->Params->ParamByName("password")->AsString = hashedPassword;
            query->Params->ParamByName("role")->AsString = "regular";
        	query->ExecSQL();

            if (query->RowsAffected > 0) {

                if (user.getUsername() != username) {
                    userChanged = true;
                }

                // create token for REST service

				UnicodeString token = CryptoUtils::createToken(FileUtils::createProjectSubDirPath("Keys") + "prv_key.bin", username, "regular");
				user = User(username, token);
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
            	LOGGER(LogLevel::Debug, "Username not available");
                OnUsernameUnavailable();
             }
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

const User& AuthenticationService::getUser() const {
	return user;
}


bool AuthenticationService::getUserChanged() const {
     return userChanged;
}

void AuthenticationService::setUserChanged(bool _userChanged) {
    userChanged = _userChanged;
}

bool AuthenticationService::verifyCredentials(const UnicodeString &username, const UnicodeString& hashedPassword, const UnicodeString& password) {

    bool verified = false;
    UnicodeString salt = CryptoUtils::generateSalt(username);
    UnicodeString hashedSalt = CryptoUtils::generateSHA256Hash(salt);

    for (int i = 1; i <= 100; i++) {

      if (CryptoUtils::generateSHA512Hash(IntToStr(i) + password + hashedSalt) == hashedPassword) {
          verified = true;
          break;
      }
    }
    return verified;
}
