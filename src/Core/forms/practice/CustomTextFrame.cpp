//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CustomTextFrame.h"

#include "UIUtils.h"
#include "TextUtils.h"
#include "EnumUtils.h"

#include "Logger.h"
#include "ENullPointerException.h"

#include <System.DateUtils.hpp>
#include <REST.Types.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrCustomText *FrCustomText;
//---------------------------------------------------------------------------
__fastcall TFrCustomText::TFrCustomText(TComponent* Owner): TFrame(Owner){}

__fastcall TFrCustomText::TFrCustomText(TComponent* Owner, TDataModule1 *_dataModule, AuthenticationService *_authService) : TFrame(Owner) {

	if (_dataModule && _authService) {

    	dataModule = _dataModule;
        authService = _authService;

		loadCustomText();

        LOGGER(LogLevel::Debug, "Created custom text frame");

	}
    else {
        throw CustomExceptions::ENullPointerException();
    }
}


void TFrCustomText::loadCustomText() {

   	dataModule->RESTClient->BaseURL = "http://localhost/RESTServer.dll/customtext";

    // add authorization header

    TRESTRequestParameter *param = dataModule->RESTRequest->Params->AddHeader("Authorization",  "Bearer " + authService->getUser().getToken());
    param->Options = param->Options << TRESTRequestParameterOption::poDoNotEncode;

    dataModule->RESTResponse->RootElement = "";
    dataModule->RESTRequest->Method = rmGET;
    dataModule->RESTRequest->Execute();

    if (dataModule->RESTResponse->StatusCode == 200) {

    	dataModule->RESTResponseDataSetAdapter->TypesMode = TJSONTypesMode::StringOnly;
        dataModule->RESTResponse->RootElement = "data";

        try {

        	TJSONArray *jsonArray = static_cast<TJSONArray*> (dataModule->RESTResponse->JSONValue);
            std::vector<UnicodeString> stringList;

            if (jsonArray) {

               for (int i = 0; i < jsonArray->Count; i++) {

                    TJSONObject *jsonObject = static_cast<TJSONObject*> (jsonArray->Items[i]);

                      if (jsonObject) {

                        if (jsonObject->Values["id"]) {
                            stringList.push_back(TextUtils::trimCharacters(jsonObject->Values["id"]->ToString(), L'\"'));
                        }

                        if (jsonObject->Values["text"]) {
                            stringList.push_back(TextUtils::trimCharacters(jsonObject->Values["text"]->ToString(), L'\"'));
                            customTexts.push_back(TextUtils::trimCharacters(jsonObject->Values["text"]->ToString(), L'\"'));
                        }
                        if (jsonObject->Values["dateModified"]) {
                            TDateTime dateModified = StrToDate(TextUtils::trimCharacters(jsonObject->Values["dateModified"]->ToString(), L'\"'), {.ShortDateFormat = "yyyy-mm-dd"});
                            stringList.push_back(FormatDateTime( "dd.mm.yyyy", dateModified));
                        }
                    }
               }
            }

            UIUtils::setListViewItems(LVCustomText, stringList, 3);

        }
        catch (const Exception &ex) {
            UIUtils::displayTimedMessage(msgDisplayTimer, LInfo, "Parsing error", TColor(0x0045FF));
        }
	}
    else {

         displayErrorMsg();
    }

 }

 void __fastcall TFrCustomText::LVCustomTextMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y) {

	if (LVCustomText->SelCount == 1) {
		BtAddSave->Caption = "Save";
		BtDelete->Enabled = true;
	}
	else if (LVCustomText->SelCount > 1) {

		TItemStates selected = TItemStates() << isSelected;
		TListItem *Item = LVCustomText->GetNextItem(Item, sdAll, selected);

		while (Item) {
			Item->Selected = false;
			Item = LVCustomText->GetNextItem(Item, sdAll, selected);
		}
	}
	else {

		if (LVCustomText->ItemFocused) {
           LVCustomText->ItemFocused->Focused = false;
		}
        resetFrameFields();
	}
}

void __fastcall TFrCustomText::LVCustomTextSelectItem(TObject *Sender, TListItem *Item, bool Selected) {

	if (LVCustomText->Selected) {

      	updateTextViewer(LVCustomText->ItemIndex);
	}
}

void TFrCustomText::updateTextViewer(int index) {

	MText->Clear();

	MText->Lines->BeginUpdate();

    if (LVCustomText->Selected->SubItems->Count >= 1) {

   	 	MText->Lines->Add(LVCustomText->Selected->SubItems->Strings[0]);
    }

    MText->Lines->EndUpdate();
}


void TFrCustomText::resetFrameFields() {

    BtAddSave->Caption = "Add";
    BtDelete->Enabled = false;

	MText->Clear();
}

void __fastcall TFrCustomText::BtAddSaveClick(TObject *Sender)
{

	if (MText->Lines->Text.IsEmpty()) {
     	ShowMessage("Text box should not be empty");
        return;
    }

    if (BtAddSave->Caption == "Add") {

         if (isNewItem(MText->Lines->Text.Trim())) {
     		addCustomText(MText->Lines->Text.Trim());
         }
         else {
         	ShowMessage("The text is already in the list");
            return;
         }
    }
    else if (BtAddSave->Caption == "Save") {

         if (MText->Lines->Text != LVCustomText->Selected->SubItems->Strings[0]) {
     		editCustomText(MText->Lines->Text.Trim(), StrToInt(LVCustomText->Selected->Caption));
         }
         else {
         	ShowMessage("Nothing was changed");
            return;
         }
     }
}

void TFrCustomText::addCustomText(const UnicodeString &text)
{
	dataModule->RESTClient->BaseURL = "http://localhost/RESTServer.dll/customtext";
    dataModule->RESTRequest->Method = rmPOST;
    executeRequest(text);
}

void TFrCustomText::editCustomText(const UnicodeString &text, const UnicodeString &id)
{
	dataModule->RESTClient->BaseURL = "http://localhost/RESTServer.dll/customtext/" + id;
    dataModule->RESTRequest->Method = rmPUT;
    executeRequest(text);

}

void TFrCustomText::deleteCustomText(const UnicodeString &text, const UnicodeString &id)
{
	dataModule->RESTClient->BaseURL = "http://localhost/RESTServer.dll/customtext/" + id;
    dataModule->RESTRequest->Method = rmDELETE;
    executeRequest("");

}


void TFrCustomText::executeRequest(const UnicodeString &text) {

    dataModule->RESTClient->ContentType = "application/json";
    dataModule->RESTResponse->RootElement = "";

    TRESTRequestParameter *param = dataModule->RESTRequest->Params->AddHeader("Authorization",  "Bearer " + authService->getUser().getToken());
    param->Options = param->Options << TRESTRequestParameterOption::poDoNotEncode;

    std::unique_ptr<TJSONObject> jsonData = std::make_unique<TJSONObject>();

    if (dataModule->RESTRequest->Method == rmPOST || dataModule->RESTRequest->Method == rmPUT) {

        jsonData->AddPair("text", text);
        jsonData->AddPair("dateModified", FormatDateTime("yyyy-mm-dd", Date()));

        dataModule->RESTRequest->AddBody(jsonData->ToString(), ctAPPLICATION_JSON);
    }

    dataModule->RESTRequest->Execute();

    if (dataModule->RESTResponse->StatusCode == 200 || dataModule->RESTResponse->StatusCode == 201) {

   		UIUtils::displayTimedMessage(msgDisplayTimer, LInfo, dataModule->RESTRequest->Method == rmPOST ? "Added" : "Saved");
        loadCustomText();
    }
    else {
       displayErrorMsg();
    }

}

void __fastcall TFrCustomText::BtDeleteClick(TObject *Sender)
{

	if (LVCustomText->Selected) {

      	updateTextViewer(LVCustomText->ItemIndex);
	}

	loadCustomText();
}

void TFrCustomText::displayErrorMsg() {

	if (dataModule->RESTResponse->StatusCode == 401) {
         UIUtils::displayTimedMessage(msgDisplayTimer, LInfo, "Unauthorized (401)", TColor(0x0045FF));
    }
    else if (dataModule->RESTResponse->StatusCode == 403) {
        UIUtils::displayTimedMessage(msgDisplayTimer, LInfo, "Forbidden (403)", TColor(0x0045FF));
    }
    else {
        UIUtils::displayTimedMessage(msgDisplayTimer, LInfo, "Server error", TColor(0x0045FF));
    }
}


bool TFrCustomText::isNewItem(const UnicodeString &text) {

    for (const UnicodeString &ct: customTexts) {
       if (ct == text) {
        	return false;
       }
    }
    return true;
}


void __fastcall TFrCustomText::msgDisplayTimerTimer(TObject *Sender)
{
      UIUtils::removeTimedMessage(msgDisplayTimer, LInfo);
}


//---------------------------------------------------------------------------

