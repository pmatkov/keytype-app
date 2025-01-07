//---------------------------------------------------------------------------

#ifndef ColorButtonH
#define ColorButtonH

#include <Vcl.StdCtrls.hpp>
#include <memory>
//---------------------------------------------------------------------------

#include <Vcl.StdCtrls.hpp>

class PACKAGE TColorButton : public Stdctrls::TButton
{

    __published:
        __property TColor BackColor = {read=FBackColor, write=SetBackColor, default=clBtnFace};
        __property TColor ForeColor = {read=FForeColor, write=SetForeColor, default=clBtnText};
        __property TColor HoverColor = {read=FHoverColor, write=SetHoverColor, default=clBtnFace};

    private:
        bool ShowBackColor;
        bool IsFocused;

        TCanvas* FCanvas;

        TColor FBackColor;
        TColor FForeColor;
        TColor FHoverColor;

        void __fastcall SetBackColor(TColor Value);
        void __fastcall SetForeColor(TColor Value);
        void __fastcall SetHoverColor(TColor Value);

    public:
        __fastcall TColorButton(TComponent* Owner);
        __fastcall ~TColorButton();

    protected:
        virtual void __fastcall CreateParams(TCreateParams &Params);
        virtual void __fastcall WndProc(TMessage &Message);
        virtual void __fastcall SetButtonStyle(bool Value);
        virtual void __fastcall DrawButton(TRect Rect, UINT State);

        void __fastcall CNMeasureItem(TWMMeasureItem &Message);
        void __fastcall CNDrawItem(TWMDrawItem &Message);
        void __fastcall WMParentFontChanged(TMessage& Message); void __fastcall SetFont(Graphics::TFont* AFont);
        void __fastcall SetEnabled(bool Value);

    BEGIN_MESSAGE_MAP
        VCL_MESSAGE_HANDLER(CN_MEASUREITEM, TWMMeasureItem, CNMeasureItem)
        VCL_MESSAGE_HANDLER(CN_DRAWITEM, TWMDrawItem, CNDrawItem)
    END_MESSAGE_MAP(TButton)
};

#endif
