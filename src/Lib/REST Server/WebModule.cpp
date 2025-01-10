
//---------------------------------------------------------------------------
#include "WebModule.h"
#include "TextUtils.h"
#include "CryptoUtils.h"

#include <vector>
#include <memory>

#include <System.JSON.hpp>
#include <System.DateUtils.hpp>
#include <System.NetEncoding.hpp>
#include <System.Character.hpp>
#include <System.SysUtils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TComponentClass WebModuleClass = __classid(TWebModule1);
//---------------------------------------------------------------------------
__fastcall TWebModule1::TWebModule1(TComponent* Owner) : TWebModule(Owner) {}

void __fastcall TWebModule1::WebModule1DefaultHandlerAction(TObject *Sender, TWebRequest *Request,
          TWebResponse *Response, bool &Handled)
{
  Response->Content =
    "<html>"
    "<head><title>REST Server App</title></head>"
    "<body>REST Server App</body>"
    "</html>";
}
//---------------------------------------------------------------------------


void __fastcall TWebModule1::WebModule1keymapGETAction(TObject *Sender, TWebRequest *Request, TWebResponse *Response, bool &Handled) {

		std::unique_ptr<TFDQuery> query = std::make_unique<TFDQuery>(nullptr);
        int id, idRow, idCol;
        UnicodeString key;

        query->Connection = MySQLDBConnection;
        std::unique_ptr<TJSONObject> jsonResponse = std::make_unique<TJSONObject>();
        std::unique_ptr<TJSONArray> jsonArray = std::make_unique<TJSONArray>();

        if (Request->QueryFields->Count == 0) {

        	query->SQL->Text = "SELECT * FROM keymapping";
            query->Open();

            if (!query->IsEmpty()) {

                while (!query->Eof) {

                   	id = query->FieldByName("id")->AsInteger;
                    idRow = query->FieldByName("idRow")->AsInteger;
                    idCol = query->FieldByName("idCol")->AsInteger;
                    key = query->FieldByName("keyValue")->AsString;

                    std::unique_ptr<TJSONObject> item = std::make_unique<TJSONObject>();

                    item->AddPair("id", IntToStr(id));
                    item->AddPair("idRow", IntToStr(idRow));
                    item->AddPair("idCol", IntToStr(idCol));
                    item->AddPair("key", key);

                    jsonArray->AddElement(item.release());

                	query->Next();

               }

               jsonResponse->AddPair("data", jsonArray.release());

            }
            query->Close();

        }
        else if (Request->QueryFields->Count == 2) {

            query->SQL->Text = "SELECT * FROM keymapping WHERE idRow = :idRow AND idCol = :idCol";

            query->Params->ParamByName("idRow")->AsString = Request->QueryFields->Values["idrow"];
            query->Params->ParamByName("idCol")->AsString = Request->QueryFields->Values["idcol"];
            query->Open();

            if (!query->IsEmpty()) {

              	id = query->FieldByName("id")->AsInteger;
            	idRow = query->FieldByName("idRow")->AsInteger;
				idCol = query->FieldByName("idCol")->AsInteger;
                key = query->FieldByName("keyValue")->AsString;

            }

            query->Close();

            jsonResponse->AddPair("id", IntToStr(id));
            jsonResponse->AddPair("idRow", IntToStr(idRow));
            jsonResponse->AddPair("idCol", IntToStr(idCol));
            jsonResponse->AddPair("key", key);

        }

        Response->ContentType = "application/json";
        Response->Content = jsonResponse->ToJSON();
}

//---------------------------------------------------------------------------
void __fastcall TWebModule1::WebModule1customtextGETAction(TObject *Sender, TWebRequest *Request, TWebResponse *Response, bool &Handled)
{

	Response->ContentType = "application/json";

	if (!isAuthenticated(Request, Handled)) {
        return;
    }

    int id;
    UnicodeString text;
    TDateTime dateModified;

    std::unique_ptr<TFDQuery> query = std::make_unique<TFDQuery>(nullptr);
    query->Connection = MySQLDBConnection;

    std::unique_ptr<TJSONObject> jsonResponse = std::make_unique<TJSONObject>();
    std::unique_ptr<TJSONArray> jsonArray = std::make_unique<TJSONArray>();

    if (Request->QueryFields->Count == 0) {

        query->SQL->Text = "SELECT * FROM customtext";
        query->Open();

        if (!query->IsEmpty()) {

            while (!query->Eof) {

                id = query->FieldByName("id")->AsInteger;
                text = query->FieldByName("text")->AsString;
                dateModified = query->FieldByName("dateModified")->AsDateTime;

                std::unique_ptr<TJSONObject> item = std::make_unique<TJSONObject>();

                item->AddPair("id", IntToStr(id));
                item->AddPair("text", text);
                item->AddPair("dateModified", FormatDateTime("yyyy-mm-dd", dateModified));

                jsonArray->AddElement(item.release());

                query->Next();

           }

           jsonResponse->AddPair("data", jsonArray.release());

        }
        query->Close();

    }
    else if (Request->QueryFields->Count == 1) {

        query->SQL->Text = "SELECT * FROM customtext WHERE id = :id";

        query->Params->ParamByName("id")->AsString = Request->QueryFields->Values["id"];
        query->Open();

        if (!query->IsEmpty()) {

            id = query->FieldByName("id")->AsInteger;
            text = query->FieldByName("text")->AsString;
            dateModified = query->FieldByName("dateModified")->AsDateTime;

        }
        query->Close();

        jsonResponse->AddPair("id", IntToStr(id));
        jsonResponse->AddPair("text", text);
        jsonResponse->AddPair("dateModified", FormatDateTime("yyyy-mm-dd", dateModified));

    }

    Response->Content = jsonResponse->ToJSON();

}
//---------------------------------------------------------------------------

void __fastcall TWebModule1::WebModule1customtextPOSTAction(TObject *Sender, TWebRequest *Request, TWebResponse *Response, bool &Handled)
{

	Response->ContentType = "application/json";

	if (!isAuthenticated(Request, Handled)) {

        return;
    }

    if (!isAuthorized(Request, Handled)) {
        return;
    }


    try {
        std::unique_ptr<TJSONValue> jsonValue(TJSONObject::ParseJSONValue(Request->Content));

        if (jsonValue) {

            TJSONObject *jsonRequest = static_cast<TJSONObject*>(jsonValue.release());

            UnicodeString text;
            TDateTime dateModified;

            if (jsonRequest->Count != 2) {
                Response->StatusCode = 400;
                Response->Content = "{\"status\":\"bad request\"}";
                Handled = true;
                return;
            }

            if (jsonRequest->Values["text"]) {
                text = TextUtils::trimCharacters(jsonRequest->Values["text"]->ToString(), L'\"');
            }
            if (jsonRequest->Values["dateModified"]) {
                dateModified = StrToDate(TextUtils::trimCharacters(jsonRequest->Values["dateModified"]->ToString(), L'\"'), {.ShortDateFormat = "yyyy-mm-dd"});
            }

            std::unique_ptr<TFDQuery> query = std::make_unique<TFDQuery>(nullptr);
   			query->Connection = MySQLDBConnection;

            query->SQL->Text = "INSERT INTO customtext (text, dateModified) VALUES (:text, :dateModified)";
            query->Params->ParamByName("text")->AsString = text;
            query->Params->ParamByName("dateModified")->AsDateTime = dateModified;

            query->ExecSQL();

             if (query->RowsAffected > 0) {
                Response->StatusCode = 201;
                Response->Content = jsonRequest->ToString();
                Handled = true;

             }
             else {
                Response->StatusCode = 500;
                Response->Content = "{\"status\":\"unable to add record\"}";
                Handled = true;
             }
             query->Close();
        }

    }
    catch (const Exception &ex) {
        Response->StatusCode = 400;
        Response->Content = "{\"status\":\"error\",\"message\":\"" + ex.Message + "\"}";
        Handled = true;
    }
}

void __fastcall TWebModule1::WebModule1customtextPUTAction(TObject *Sender, TWebRequest *Request, TWebResponse *Response, bool &Handled)
{
  	Response->ContentType = "application/json";

	if (!isAuthenticated(Request, Handled)) {
        return;
    }

    if (!isAuthorized(Request, Handled)) {
        return;
    }

    try {
        std::unique_ptr<TJSONValue> jsonValue(TJSONObject::ParseJSONValue(Request->Content));

        if (jsonValue) {

            TJSONObject *jsonRequest = static_cast<TJSONObject*>(jsonValue.release());

            if (jsonRequest->Count != 2 || !jsonRequest->Values["text"] || !jsonRequest->Values["dateModified"]) {
                Response->StatusCode = 400;
                Response->Content = "{\"status\":\"bad request\"}";
                return;
            }

            UnicodeString text = TextUtils::trimCharacters(jsonRequest->Values["text"]->ToString(), L'\"');
            TDateTime dateModified = StrToDate(TextUtils::trimCharacters(jsonRequest->Values["dateModified"]->ToString(), L'\"'), {.ShortDateFormat = "yyyy-mm-dd"});

            // split path endpoint and id param (customtext/{id})
            std::vector<UnicodeString> pathSegments = TextUtils::splitToTokens(ExtractFileName(Request->PathInfo), '/');

            std::unique_ptr<TFDQuery> query = std::make_unique<TFDQuery>(nullptr);
    		query->Connection = MySQLDBConnection;

            query->SQL->Text = "UPDATE customtext SET text = :text, dateModified = :dateModified WHERE id = :id";
            query->Params->ParamByName("text")->AsString = text;
            query->Params->ParamByName("dateModified")->AsDateTime = dateModified;
            query->Params->ParamByName("id")->AsInteger = StrToInt(pathSegments[1]);

            query->ExecSQL();

             if (query->RowsAffected > 0) {
                Response->StatusCode = 200;
                Response->Content = jsonRequest->ToString();
                Handled = true;

             }
             else {
                Response->StatusCode = 500;
                Handled = true;
                Response->Content = "{\"status\":\"unable to change record\"}";
             }
             query->Close();
        }
        else {
            Response->StatusCode = 400;
            Response->Content = "{\"status\":\"bad request\"}";
            Handled = true;
            return;
        }

    }
    catch (const Exception &ex) {
        Response->StatusCode = 400;
        Response->Content = "{\"status\":\"error\",\"message\":\"" + ex.Message + "\"}";
        Handled = true;
    }
}


bool TWebModule1::isAuthenticated(TWebRequest *Request, bool &Handled) {

    if (Request->Authorization.IsEmpty()) {
    	Response->StatusCode = 401;
    	Response->Content = "{\"status\":\"No credentials provided\"}";
        Handled = true;
        return false;
    }

    UnicodeString token = Request->Authorization.SubString(8, Request->Authorization.Length());

    if (!CryptoUtils::verifyToken("C:\\inetpub\\wwwroot\\pub_key.bin", token)) {

    	Response->StatusCode = 401;
    	Response->Content = "{\"status\":\"Invalid credentials\"}";
        Handled = true;
        return false;
    }

    return true;
}

bool TWebModule1::isAuthorized(TWebRequest *Request, bool &Handled) {

    // extract token from authorization header

    UnicodeString token = Request->Authorization.SubString(8, Request->Authorization.Length());

    std::vector<UnicodeString> tokens = TextUtils::splitToTokens(token, '.');
    UnicodeString decodedPayload = CryptoUtils::decodeBase64URLToString(tokens[1]);

    std::unique_ptr<TJSONValue> jsonValue(TJSONObject::ParseJSONValue(decodedPayload));
    TJSONObject *jsonPayload = static_cast<TJSONObject*>(jsonValue.get());

    UnicodeString role = "";

    if (jsonPayload->Values["role"]) {
        role = TextUtils::trimCharacters(jsonPayload->Values["role"]->ToString(), L'\"');
    }

    if (role != "superuser") {

        Response->StatusCode = 403;
    	Response->Content = "{\"status\":\"Unauthorized\"}";
        Handled = true;
     	return false;
    }

   return true;
}


void __fastcall TWebModule1::WebModuleBeforeDispatch(TObject *Sender, TWebRequest *Request, TWebResponse *Response, bool &Handled)
{

	if (Request->MethodType == mtPut) {

    	std::vector<UnicodeString> pathSegments = TextUtils::splitToTokens(ExtractFileName(Request->PathInfo), '/');
    	int value;

        if (pathSegments.size() == 2 && TryStrToInt(pathSegments[1], value)) {

    		WebModule1customtextPUTAction(Sender, Request, Response, Handled);
    	}
    }
}


