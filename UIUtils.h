//---------------------------------------------------------------------------

#ifndef UIUtilsH
#define UIUtilsH
//---------------------------------------------------------------------------

#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <vcl.h>
#include <memory>

class UIUtils {

	public:
		static void setCharStyle(TRichEdit* richedit, int charIndex, TFontStyle style, bool enabled);
		static void setCharColor(TRichEdit* richedit, int charIndex, TColor textColor);
		static void setTextColor(TRichEdit* richedit, TColor textColor);

    template<typename T>
    static void createFrame(std::unique_ptr<T>& frame, TWinControl* parent) {
        frame = std::make_unique<T>(parent);
        frame->Parent = parent;
        frame->Align = alClient;
    }
    template<typename T>
    static void setFrameVisibility(std::unique_ptr<T>& frame, bool visibility){
        frame->Visible = visibility;
    }

    template<typename T1, typename T2>
    static void switchFrames(std::unique_ptr<T1>& frameToSwitchOff, std::unique_ptr<T2>& frameToSwitchOn) {
        setFrameVisibility(frameToSwitchOff, false);
        setFrameVisibility(frameToSwitchOn, true);
    }

    static void switchActiveControl(TWinControl* controlToEnable, TWinControl* controlToDisable) {
        controlToEnable->Enabled = true;
        controlToDisable->Enabled = false;
    }


    static void enableChildControls(TWinControl* parent);
    static void disableChildControls(TWinControl* parent);

};

#endif
