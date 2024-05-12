//---------------------------------------------------------------------------

#pragma hdrstop

#include <FireDAC.DApt.hpp>

#include "AuthenticationService.h"
#include "ENullPointerException.h"
#include "User.h"
#include "Logger.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

AuthenticationService::AuthenticationService(TDataModule1 *_dataModule) {

    if (_dataModule) {
       dataModule = _dataModule;
       LOGGER(LogLevel::Debug, "Authentication service created");
    }
    else {
        throw CustomExceptions::ENullPointerException();
    }
}

bool AuthenticationService::loginUser(const UnicodeString& username, const UnicodeString& password) {

	if (username.Compare("guest") == 0) {

        user = User();
		authenticated = true;
        LOGGER(LogLevel::Info, "User signed in as <guest>");

		return true;
	}

    std::unique_ptr<TFDQuery> query = std::make_unique<TFDQuery>(nullptr);
    try {

    	// locate?
        query->Connection = dataModule->MySQLDBConnection;
        query->SQL->Text = "SELECT * FROM users WHERE username = :username AND password = :password";
        query->Params->ParamByName("username")->AsString = username;
        query->Params->ParamByName("password")->AsString = password;
        query->Open();

        if (!query->IsEmpty()) {

        	user = User(username, password);
			authenticated = true;

        	query->Close();

            LOGGER(LogLevel::Info, "User signed in as <" + username + ">");
        	return true;
        }
		else {
        	query->Close();
        	return false;
        }
    } catch (Exception &ex) {
    	LOGGER(LogLevel::Fatal, ex.Message);
    }

    return false;
}

bool  AuthenticationService::logoutUser() {

	if (authenticated) {

    	LOGGER(LogLevel::Info, "User signed out");

        user = User();
		authenticated = false;

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

            query->Close();
            query->SQL->Text = "INSERT INTO users (username, password) VALUES (:username, :password)";
            query->Params->ParamByName("username")->AsString = username;
            query->Params->ParamByName("password")->AsString = password;
        	query->ExecSQL();

            if (query->RowsAffected > 0) {

            	user = User(username, password);
				authenticated = true;
                query->Close();
                LOGGER(LogLevel::Info, "User registered as <" + username + ">");
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

const User& AuthenticationService::getUser() const {
	return user;
}
