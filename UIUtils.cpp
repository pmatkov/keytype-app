//---------------------------------------------------------------------------

#include "UIUtils.h"
#include "TextUtils.h"
#include "FileUtils.h"
#include "Generator.h"
#include "Logger.h"
#include "reinit.hpp"
#include "EFileNotFoundException.h"

#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)


/* interposer class to bypass limitation for accessing
protected class member (changeFontFamily function)  */

class TInterposerControl : public TControl
{
    public:
        __property Font;
};

namespace UIUtils {

    // RichEdit style

    void setCharStyle(TRichEdit* richedit, int charIndex, TFontStyle style, bool enabled) {

        if (charIndex >= 0 && charIndex < richedit->Text.Length()) {

            richedit->SelStart = charIndex;
            richedit->SelLength = 1;

            if (enabled)
                richedit->SelAttributes->Style = richedit->SelAttributes->Style << style;
            else
              richedit->SelAttributes->Style = richedit->SelAttributes->Style >> style;
        }
    }

    void setCharColor(TRichEdit* richedit, int charIndex, TColor textColor) {

        if (charIndex >= 0 && charIndex < richedit->Text.Length()) {

            richedit->SelStart = charIndex;
            richedit->SelLength = 1;
            richedit->SelAttributes->Color = textColor;
        }
    }

    void setCharColor(TRichEdit* richedit, const std::vector<std::pair<UnicodeString, bool>>& text, TColor textColor) {

        for (int i = 0; i < text.size(); i++) {

        	richedit->SelStart = i;
            richedit->SelLength = 1;

            if (text[i].second) {
                richedit->SelAttributes->Color = textColor;
            }
            else {
                 richedit->SelAttributes->Color = clSilver;
            }
        }
    }

    void setCharColor(TRichEdit* richedit, const std::vector<std::pair<UnicodeString, bool>>& text, int insertStart, int insertEnd, TColor textColor) {

        for (int i = insertStart; i < insertEnd; i++) {

        	richedit->SelStart = i;
            richedit->SelLength = 1;

            richedit->SelAttributes->Color = textColor;
        }

        if (text.size()) {

			setCharColor(richedit, text, textColor);
        }
    }


    void setCharBgColor(TRichEdit *richedit, int charIndex, TColor color) {

    	if (charIndex >= 0 && charIndex < richedit->Text.Length()) {

            richedit->SelStart = charIndex;
            richedit->SelLength = 1;

            CHARFORMAT2 cf;
            cf.cbSize = sizeof(CHARFORMAT2);
            cf.dwMask = CFM_BACKCOLOR;
            cf.crBackColor = ColorToRGB(color);

            richedit->Perform(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
        }
    }

    void setTextColor(TRichEdit* richedit, TColor textColor) {

        richedit->SelStart = 0;
        richedit->SelLength = richedit->Text.Length();
        richedit->SelAttributes->Color = textColor;
    }


   // determine max chars for RichEdit control

    int countMaxChars(TRichEdit *RETextBox, const UnicodeString &string) {

        try {
            std::unique_ptr<TBitmap> bitmap = std::make_unique<TBitmap>();
            std::unique_ptr<TCanvas> canvas = std::make_unique<TCanvas>();
            canvas->Handle = bitmap->Canvas->Handle;

            canvas->Font = RETextBox->Font;

            int textWidth = canvas->TextWidth(string);
            int textHeight = canvas->TextHeight(string);
            UnicodeString cpString = string;

            int maxChars = 0;
            bool oversized;

            for (int i = 0; i < RETextBox->ClientHeight/ textHeight; i++) {

                oversized = false;

                while ((float)(RETextBox->ClientWidth/ textWidth) < 1.0f || ((float)(RETextBox->ClientWidth/ textWidth) >= 1.0f && TextUtils::isWordBreak(string, cpString.Length()))) {
                    oversized = true;
                    cpString.Delete(cpString.Length(), 1);
                    textWidth = canvas->TextWidth(cpString);
                }
                maxChars += cpString.Length();

                if (oversized) {
                    cpString = string;
                    cpString.Delete(1, maxChars);
                    textWidth = canvas->TextWidth(cpString);
                }
                else {
                    break;
                }

            }

            return maxChars;

        } catch (Exception &ex) {
              LOGGER(LogLevel::Fatal, "Exception");
              throw Exception("");
        }

    }

    // estimate max chars for RichEdit control (for random text)

    int estimateMaxChars(TRichEdit *RETextBox) {

      	std::unique_ptr<TBitmap> bitmap = std::make_unique<TBitmap>();
        std::unique_ptr<TCanvas> canvas = std::make_unique<TCanvas>();
        canvas->Handle = bitmap->Canvas->Handle;

        canvas->Font = RETextBox->Font;
        int charWidth = canvas->TextWidth("o");
        int charHeight = canvas->TextHeight("o");

        int initialEstimate = (RETextBox->ClientWidth / charWidth) * (RETextBox->ClientHeight / charHeight);
        int finalEstimate[3];

        int splitSize = 100;

        UnicodeString sampleText = Generator::generateChars("abcdefghijklmnopqrstuvwxyz", initialEstimate * 2);

        for (int i = 0; i < 3; i++) {
            UnicodeString generatedText = sampleText.SubString(1, splitSize * (i + 1));

            int textWidth = canvas->TextWidth(generatedText);
            int textHeight = canvas->TextHeight(generatedText);

            finalEstimate[i] = generatedText.Length() - generatedText.Length() * 0.1;
        }

        std::sort(std::begin(finalEstimate), std::end(finalEstimate));

        return finalEstimate[1];

    }

   // child controls

    void enableChildControls(TWinControl* parent, bool enable)
    {
        for (int i = 0; i < parent->ControlCount; i++) {

            TControl* child = parent->Controls[i];
            child->Enabled = enable;
        }
    }

    void showChildControls(TWinControl* parent, bool show)
    {
        for (int i = 0; i < parent->ControlCount; i++) {

            TControl* child = parent->Controls[i];
            child->Visible = show;
        }
    }


    void switchControl(TWinControl* firstControl, TWinControl* secondControl) {
        firstControl->Enabled = false;
        secondControl->Enabled = true;
    }


    // font family for child controls

    void changeFontFamily(TWinControl *Control, const UnicodeString fontFamily) {

        for (int i = 0; i < Control->ControlCount; i++)    {
            TControl *control = Control->Controls[i];

            if (control->InheritsFrom(__classid(TWinControl))) {
                changeFontFamily(static_cast<TWinControl*>(control), fontFamily);
            }

            TInterposerControl *interposerControl = static_cast<TInterposerControl*>(control);
            interposerControl->Font->Name = fontFamily;
        }
    }


    // Fonts

     std::vector<UnicodeString> getScreenFonts() {

        std::vector<UnicodeString> list;

        for (int i = 0; i < Screen->Fonts->Count; i++) {

            if (Screen->Fonts->Strings[i].SubString1(1, 2).Compare("Ar") >= 0 && Screen->Fonts->Strings[i].SubString1(1, 2).Compare("Vi") <= 0) {

                list.push_back(Screen->Fonts->Strings[i]);
            }
        }
        return list;
    }

    // ComboBox

    void addComboBoxItem(TComboBox *comboBox, const UnicodeString &item, int selectedIndex) {

        comboBox->Items->Clear();
        comboBox->Items->Add(item);
        comboBox->ItemIndex = selectedIndex;
    }

    void selectComboBoxItem(TComboBox *comboBox, int selectedIndex) {

        comboBox->ItemIndex = selectedIndex;
    }

    void selectComboBoxItem(TComboBox *comboBox, const UnicodeString &item) {

    	int index = comboBox->Items->IndexOf(item);

    	if (index != -1) {
        	selectComboBoxItem(comboBox, index);
        }
    }

    void setComboBoxItems(TComboBox *comboBox, const std::vector<UnicodeString> &items, int selectedIndex) {

        comboBox->Items->Clear();

        for (const UnicodeString &item : items) {
            comboBox->Items->Add(item);
        }

        comboBox->ItemIndex = selectedIndex;
    }

    void setComboBoxItems(TComboBox *comboBox, const std::vector<UnicodeString> &items, const UnicodeString &selectedItem) {

        comboBox->Items->Clear();
        int index = -1;

        for (int i= 0; i < items.size(); i++) {

            if (items[i].LowerCase() == selectedItem.LowerCase()) {

             index = i;

            }
            comboBox->Items->Add(items[i]);
        }

        comboBox->ItemIndex = index;
    }

    // ListView items

    void setListViewItems(TListView *listview, const std::vector<UnicodeString> &items) {

        listview->Items->Clear();
        listview->Items->BeginUpdate();

        for (const UnicodeString &item : items) {

            TListItem *listItem = listview->Items->Add();
            listItem->Caption = item;
        }
        listview->Items->EndUpdate();
	}

    void setListViewItems(TListView *listview, const std::vector<UnicodeString> &items, int index) {

        listview->Items->Clear();
        listview->Items->BeginUpdate();

        for (int i = 0; i < items.size(); i += index) {

        	TListItem* listItem = listview->Items->Add();
            listItem->Caption = items[i];
            for (int j = i + 1; j < i + index; j++) {

                if (items[j] == "Unknown") {
                     continue;
                }
                listItem->SubItems->Add(items[j]);
            }
        }
        listview->Items->EndUpdate();
	}


    // Edit

    void setEditText(TEdit *edit, const UnicodeString &text) {

        edit->Text = text;
    }

    int findItemIndex(const std::vector<UnicodeString> &items, const UnicodeString &itemToSearch) {
          for (int i= 0; i < items.size(); i++) {

            if (items[i].LowerCase() == itemToSearch.LowerCase()) {

             return i;

            }
        }
        return -1;
    }


    // language

    void changeLanguage(Language language) {

    	bool loaded = false;

         if (language == Language::English || language == Language::Unknown) {
            const int ENGLISH = (SUBLANG_ENGLISH_UK << 10) | LANG_ENGLISH;
            loaded = LoadNewResourceModule(ENGLISH);
         }
         else if (language == Language::Croatian) {
            const int CROATIAN = (SUBLANG_CROATIAN_CROATIA << 10) | LANG_CROATIAN;
            loaded = LoadNewResourceModule(CROATIAN);
         }

         if (loaded) {
         	ReinitializeForms();
         }
    }

    // file dialog

    void setFileDialogProperties(TOpenTextFileDialog *FileDialog, const UnicodeString &dir, const UnicodeString &filter) {

        FileDialog->InitialDir = FileUtils::createAbsolutePath(dir, false);
        FileDialog->Filter = "Text files|*." + filter.UpperCase();
    }

    void displayTimedMessage(TTimer *timer, TLabel *label, const UnicodeString &msg) {
    	label->Font->Color = clBlue;
        label->Caption = msg;
        timer->Enabled = true;
    }

    void removeTimedMessage(TTimer *timer, TLabel *label) {
        label->Caption = "";
        timer->Enabled = false;
    }

    void higlightMessage(TTimer *timer, TLabel *label, TColor color) {
    	label->Font->Color = color;
        timer->Enabled = true;
    }

    void removeHiglightMessage(TTimer *timer, TLabel *label) {
        label->Font->Color = clBlack;
        timer->Enabled = false;
    }
}

