//---------------------------------------------------------------------------

#ifndef UIUtilsH
#define UIUtilsH
//---------------------------------------------------------------------------

#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <vcl.h>
#include <memory>
#include <utility>

#include "Parser.h"
#include "AuthenticationService.h"

namespace UIUtils {

    void setCharStyle(TRichEdit* richedit, int charIndex, TFontStyle style, bool enabled);
    void setCharColor(TRichEdit* richedit, int charIndex, TColor textColor);
    void setCharColor(TRichEdit* richedit, const std::vector<std::pair<UnicodeString, bool>>& text, TColor textColor);
    void setCharColor(TRichEdit* richedit, const std::vector<std::pair<UnicodeString, bool>>& text, int insertStart, int insertEnd, TColor textColor);
    void setCharBgColor(TRichEdit *richEdit, int charIndex, TColor color);
    void setTextColor(TRichEdit* richedit, TColor textColor);
    std::vector<UnicodeString> getScreenFonts();

    int countMaxChars(TRichEdit *RETextBox, const UnicodeString &string);
    int estimateMaxChars(TRichEdit *RETextBox);

    void enableChildControls(TWinControl* parent);
    void disableChildControls(TWinControl* parent);
    void switchControl(TWinControl* firstControl, TWinControl* secondControl);

    void changeFontFamily(TWinControl *Control, const UnicodeString fontFamily);

    void setComboBoxItems(TComboBox *comboBox, const std::vector<UnicodeString> &items, int defaultIndex);
    void setComboBoxItems(TComboBox *comboBox, const std::vector<UnicodeString> &items, const UnicodeString &selectedItem);
    int findItemIndex(const std::vector<UnicodeString> &items, const UnicodeString &selectedItem);

    void changeLanguage(Language language);

    template<typename T>
    std::unique_ptr<T> createFrame(TWinControl* parent) {
        std::unique_ptr<T> frame = std::make_unique<T>(parent);
        frame->Parent = parent;
        frame->Align = alClient;
        return frame;
    }

    template<typename T,  typename... Args>
    std::unique_ptr<T> createFrame(TWinControl* parent, Args&&... args) {
        std::unique_ptr<T> frame = std::make_unique<T>(parent, std::forward<Args>(args)...);
        frame->Parent = parent;
        frame->Align = alClient;
        return frame;
    }

    template<typename T>
    void setFrameVisibility(std::unique_ptr<T>& frame, bool visibility){
        frame->Visible = visibility;
    }

    template<typename T1, typename T2>
    void switchFrames(std::unique_ptr<T1>& firstFrame, std::unique_ptr<T2>& secondFrame) {
        setFrameVisibility(firstFrame, false);
        setFrameVisibility(secondFrame, true);
    }

    template<typename T>
    void setFrameVisibility(T *frame, bool visibility){
        frame->Visible = visibility;
    }

    template<typename T1, typename T2>
    void switchFrames(T1 *firstFrame, T2 *secondFrame) {
        setFrameVisibility(firstFrame, false);
        setFrameVisibility(secondFrame, true);
    }


};

#endif
