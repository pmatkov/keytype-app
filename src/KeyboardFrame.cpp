//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "KeyboardFrame.h"
#include "TypingSettings.h"
#include "Logger.h"
#include "ENullPointerException.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrKeyboard *FrKeyboard;
//---------------------------------------------------------------------------
__fastcall TFrKeyboard::TFrKeyboard(TComponent* Owner) : TFrame(Owner) {}


void TFrKeyboard::setDataModule(TDataModule1 *_dataModule) {

   	if (_dataModule) {

       dataModule = _dataModule;
       LOGGER(LogLevel::Debug, "Created keyboard frame");

	}
    else {
        throw CustomExceptions::ENullPointerException();
    }
}

void TFrKeyboard::setMainSession(MainSession *_mainSession) {

   	if (_mainSession) {

       mainSession = _mainSession;
       generateKeyboardLayout();

	}
    else {
        throw CustomExceptions::ENullPointerException();
    }

}

void TFrKeyboard::generateKeyboardLayout()
{

	std::vector<UnicodeString> row;

    int xPos = 10, yPos = 10, buttonHeight = 20, index = 0;

   	dataModule->RESTClient->BaseURL = "http://localhost/RESTServer.dll/keymap";
    dataModule->RESTRequest->Method = rmGET;
   	dataModule->RESTRequest->Execute();

    dataModule->RESTResponseDataSetAdapter->TypesMode = TJSONTypesMode::StringOnly;
    dataModule->RESTResponse->RootElement = "data";

    if (dataModule->FDMemTable->RecordCount) {

        while (!dataModule->FDMemTable->Eof)  {

            int idRow = dataModule->FDMemTable->FieldByName("idRow")->AsInteger;
            int idCol = dataModule->FDMemTable->FieldByName("idCol")->AsInteger;
            UnicodeString key = dataModule->FDMemTable->FieldByName("key")->AsWideString;

            if (mainSession->getTypingSettings().getKeyboardLayout() == KeyboardLayout::Dvorak) {
              	key = dataModule->translateKey(key);
            }

            if (idRow > index) {
                generateKeyboardRow(PKeyboardBase, xPos, yPos, row);
                yPos += buttonHeight;
                row.clear();
                index = idRow;
            }

            row.push_back(key);

            dataModule->FDMemTable->Next();
        }
          if (!row.empty()) {
            generateKeyboardRow(PKeyboardBase, xPos, yPos, row);
            yPos += buttonHeight;
        }
    }
}

void TFrKeyboard::generateKeyboardRow(TWinControl* parent, int xPos, int yPos, const std::vector<UnicodeString>& captions)
{

    int height = 20;

    const TColor bgColor = clWhite;
    const TColor fgColor = clBlack;

    for (const UnicodeString& caption : captions)
    {

     	int width = 20;

        if (caption == "Caps" || caption == "Enter" || caption == "Lsh" || caption == "Alt") {
        	width *= 1.5;
        }
        else if (caption == "Tab" || caption == "Bsp") {
           width *= 2;
        }
        else if (caption == "Rsh" || caption == "Ctrl") {
        	width *= 2.5;
        }
        else if (caption == "Space") {
        	width *= 7;
        }

        std::unique_ptr<TColorButton> button = std::make_unique<TColorButton>(parent);

        initializeColorButton(button.get(), parent, bgColor, fgColor, width, height, caption);

        button->Left = xPos;
        button->Top = yPos;

        xPos += width;

        buttons.push_back(std::move(button));
    }
}

void TFrKeyboard::initializeColorButton(TColorButton* button, TWinControl* parent, TColor bgColor, TColor fgColor, int width, int height, const UnicodeString& caption)
{
    button->Parent = parent;

    button->BackColor = bgColor;
    button->ForeColor = fgColor;

    button->Width = width;
    button->Height = height;

    button->Caption = caption;

    button->Enabled = false;
    button->OnMouseEnter = nullptr;
    button->OnMouseLeave = nullptr;
}

void TFrKeyboard::highlightKey(const UnicodeString& keyCaption, bool setColor) {


    for (const std::unique_ptr<TColorButton> &button: buttons) {
       if (button->Caption == keyCaption) {
          	button->BackColor = setColor ? TColor(0x60A4F4) : clWhite;
       }
    }
}
