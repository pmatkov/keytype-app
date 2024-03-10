//---------------------------------------------------------------------------

#pragma hdrstop

#include "AuthenticationService.h"
#include "ENullPointerException.h"
#include "User.h"
#include "Logger.h"
#include <FireDAC.DApt.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)

AuthenticationService::AuthenticationService(MainSession *_mainSession, TDataModule1 *_dataModule) {

    if (_mainSession) {
       mainSession = _mainSession;
       dataModule = _dataModule;
       LOGGER(LogLevel::Debug, "Authentication service created");
    }
    else {
        throw ENullPointerException();
    }
}

bool AuthenticationService::loginUser(const UnicodeString& username, const UnicodeString& password) {

	if (username.Compare("guest") == 0) {

        mainSession->setUser(User());
		mainSession->setAuthenticated(true);
		return true;
	}

    std::unique_ptr<TFDQuery> query = std::make_unique<TFDQuery>(nullptr);
    try {
        query->Connection = dataModule->MySQLDBConnection;
        query->SQL->Text = "SELECT * FROM users WHERE username = :username AND password = :password";
        query->Params->ParamByName("username")->AsString = username;
        query->Params->ParamByName("password")->AsString = password;
        query->Open();

        if (!query->IsEmpty()) {

        	mainSession->setUser(User(username));
			mainSession->setAuthenticated(true);
        	query->Close();
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

	if (mainSession->isAuthenticated()) {

    	LOGGER(LogLevel::Info, "User logged out");

        mainSession->setUser(User());
		mainSession->setAuthenticated(false);
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

            	mainSession->setUser(User(username));
                mainSession->setAuthenticated(true);
                query->Close();
                return true;
            }
            else {
                query->Close();
        		return false;
            }

        } else {
        	query->Close();

            if (OnUsernameUnavailable) {
                OnUsernameUnavailable();
             }
             return false;
        }

    } catch (Exception &ex) {
    	LOGGER(LogLevel::Fatal, ex.Message);
    }

    return false;

}
