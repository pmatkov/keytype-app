//---------------------------------------------------------------------------
#undef UNICODE
#define UNICODE

#pragma hdrstop

#include "ColorButton.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TColorButton::TColorButton(Classes::TComponent* Owner)  : TButton(Owner)
{
    ShowBackColor = true;
    FCanvas = new TCanvas;

    FBackColor = clBtnFace;
    FForeColor = clBtnText;
    FHoverColor = clBtnFace;
}

__fastcall TColorButton::~TColorButton()
{
    delete FCanvas;
}


void __fastcall TColorButton::CreateParams(Controls::TCreateParams &Params)
{
    TButton::CreateParams(Params);
    Params.Style |= BS_OWNERDRAW;
}

void __fastcall TColorButton::WndProc(Messages::TMessage &Message)
{
    if (Message.Msg == CM_MOUSELEAVE)
    {
        ShowBackColor = true;
        Invalidate();
    }
    if (Message.Msg == CM_MOUSEENTER)
    {
        ShowBackColor = false;
        Invalidate();
    }
    TButton::WndProc(Message);
}

void __fastcall TColorButton::SetButtonStyle(bool Value)
{
    if (Value != IsFocused)
    {
        IsFocused = Value;
        Invalidate();
    }
}

void __fastcall TColorButton::DrawButton(TRect Rect, UINT State)
{
  	bool IsDown = (State & ODS_SELECTED) != 0;
    bool IsDisabled = (State & ODS_DISABLED) != 0;
    bool IsDefault = (State & ODS_FOCUS) != 0;


    DWORD Flags = DFCS_BUTTONPUSH | DFCS_ADJUSTRECT;
    if (IsDown)
        Flags |= DFCS_PUSHED;
    if (IsDisabled)
        Flags |= DFCS_INACTIVE;

    if (IsDefault || IsFocused)
    {

        FCanvas->Pen->Color = clWindowFrame;
        FCanvas->Pen->Width = 1;
        FCanvas->Brush->Style = bsClear;
        FCanvas->Rectangle(Rect.Left, Rect.Top, Rect.Right, Rect.Bottom);
        InflateRect(&Rect, -1, -1);
    }
    else
    {
        DrawFrameControl(FCanvas->Handle, &Rect, DFC_BUTTON, Flags);
    }

    FCanvas->Brush->Color = IsDown ? clBtnFace : (ShowBackColor ? FBackColor : FHoverColor);
    FCanvas->FillRect(Rect);

    FCanvas->Font = Font;
    FCanvas->Font->Color = IsDisabled ? clGrayText : FForeColor;
    DrawText(FCanvas->Handle, Caption.c_str(), -1, &Rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}


void __fastcall TColorButton::WMParentFontChanged(Messages::TMessage& Message)
{
    TButton::Dispatch(&Message);
    Invalidate();
}

void __fastcall TColorButton::SetEnabled(bool Value)
{
    TButton::SetEnabled(Value);

    Invalidate();
}

void __fastcall TColorButton::CNMeasureItem(Messages::TWMMeasureItem &Message)
{
    Message.MeasureItemStruct->itemWidth = Width;
    Message.MeasureItemStruct->itemHeight = Height;
}

void __fastcall TColorButton::CNDrawItem(Messages::TWMDrawItem &Message)
{
    TCanvas *SaveCanvas;
    SaveCanvas = FCanvas;
    FCanvas->Handle = Message.DrawItemStruct->hDC;
    try
    {
        TRect Rect;
        Rect = Message.DrawItemStruct->rcItem;
        DrawButton(Rect, Message.DrawItemStruct->itemState);
    }
    __finally
    {
        FCanvas->Handle = 0;
        FCanvas = SaveCanvas;
    }
    Message.Result = 1;
}

void __fastcall TColorButton::SetBackColor(TColor Value)
{
    if (FBackColor != Value)
    {
        FBackColor = Value;
        Invalidate();
    }
}

void __fastcall TColorButton::SetForeColor(TColor Value)
{
    if (FForeColor != Value)
    {
        FForeColor = Value;
        Invalidate();
    }
}

void __fastcall TColorButton::SetHoverColor(TColor Value)
{
    if (FHoverColor != Value)
    {
        FHoverColor = Value;
        Invalidate();
    }
}
