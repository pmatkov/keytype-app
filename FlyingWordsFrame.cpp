//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FlyingWordsFrame.h"
#include "Factory.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrFlyingWords *FrFlyingWords;
//---------------------------------------------------------------------------
__fastcall TFrFlyingWords::TFrFlyingWords(TComponent* Owner) : TFrame(Owner), gameEngine(ModelFactory::createGameEngine(*this, *this)){ }

void __fastcall TFrFlyingWords::LStartClick(TObject *Sender)
{
    LStart->Visible = false;
    Timer1->Enabled = true;
    gameEngine->initializeGame(0, this->ClientHeight, 0, this->ClientWidth);
}

void TFrFlyingWords::setItemSingleItemControl(const UnicodeString& componentName, const UnicodeString& item) {

}
void TFrFlyingWords::selectItemMultiItemControl(const UnicodeString& componentName, const UnicodeString& item) {

}
void TFrFlyingWords::setItemsMultiItemControl(const UnicodeString& componentName, const std::vector<UnicodeString>& items, int selectedIndex) {

}
void TFrFlyingWords::addItemMultiItemControl(const UnicodeString& componentName, const UnicodeString& item, int selectedIndex) {

}

bool TFrFlyingWords::createTextControl(const UnicodeString& text, const UnicodeString& color) {
    LflyingWords.push_back(std::make_unique<TLabel>(this));

    if (LflyingWords[LflyingWords.size()-1]) {
        LflyingWords[LflyingWords.size()-1]->Parent = this;
        LflyingWords[LflyingWords.size()-1]->Caption = text;
        LflyingWords[LflyingWords.size()-1]->Color = StringToColor(color);

        return true;
    }

    return false;
}

bool TFrFlyingWords::removeTextControl(int index) {

   	if (index >= 0 && index < LflyingWords.size())
    {
        LflyingWords[index].reset();
        LflyingWords.erase(LflyingWords.begin() + index);

        return true;
    }

    return false;
}

bool TFrFlyingWords::moveTextControl(int index, int x, int y) {

	if (index >= 0 && index < LflyingWords.size())
    {
        LflyingWords[index]->Top = y;
        LflyingWords[index]->Left = x;

        return true;
    }

    return false;
}

int TFrFlyingWords::getTextHeight(int index) {
     return LflyingWords[index]->Height;
}

int TFrFlyingWords::getTextWidth(int index) {
     return LflyingWords[index]->Width;
}


void __fastcall TFrFlyingWords::Timer1Timer(TObject *Sender)
{
    gameEngine->moveWords();
}
//---------------------------------------------------------------------------

