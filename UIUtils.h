//---------------------------------------------------------------------------

#ifndef UIUtilsH
#define UIUtilsH
//---------------------------------------------------------------------------

#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <vcl.h>
#include <memory>

#include "Parser.h"
#include "PracticeSession.h"

class UIUtils {

	public:
		static void setCharStyle(TRichEdit* richedit, int charIndex, TFontStyle style, bool enabled);
		static void setCharColor(TRichEdit* richedit, int charIndex, TColor textColor);
		static void setTextColor(TRichEdit* richedit, TColor textColor);


    template<typename T>
    static std::unique_ptr<T> createFrame(TWinControl* parent) {
        std::unique_ptr<T> frame = std::make_unique<T>(parent);
        frame->Parent = parent;
        frame->Align = alClient;
        return frame;
    }


    template<typename T>
    static std::unique_ptr<T> createFrame(TWinControl* parent, Parser *parser, PracticeSession *practiceSession) {
        std::unique_ptr<T> frame = std::make_unique<T>(parent, parser, practiceSession);
        frame->Parent = parent;
        frame->Align = alClient;
        return frame;
    }

    template<typename T>
    static void setFrameVisibility(std::unique_ptr<T>& frame, bool visibility){
        frame->Visible = visibility;
    }

    template<typename T1, typename T2>
    static void switchFrames(std::unique_ptr<T1>& firstFrame, std::unique_ptr<T2>& secondFrame) {
        setFrameVisibility(firstFrame, false);
        setFrameVisibility(secondFrame, true);
    }

    static void switchControl(TWinControl* firstControl, TWinControl* secondControl) {
        firstControl->Enabled = false;
        secondControl->Enabled = true;
    }

    static void enableChildControls(TWinControl* parent);
    static void disableChildControls(TWinControl* parent);

};

#endif
