//---------------------------------------------------------------------------

#ifndef CustomTextFrameH
#define CustomTextFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XmlTransform.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.XMLIntf.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ToolWin.hpp>

#include "DataModule.h"
#include <Data.DB.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>

#include "AuthenticationService.h"

//---------------------------------------------------------------------------
class TFrCustomText : public TFrame
{
__published:	// IDE-managed Components
	TMemo *MText;
	TButton *BtAddSave;
	TLabel *LInfo;
	TTimer *msgDisplayTimer;
	TButton *BtDelete;
	TListView *LVCustomText;
	void __fastcall BtAddSaveClick(TObject *Sender);
	void __fastcall msgDisplayTimerTimer(TObject *Sender);
	void __fastcall BtDeleteClick(TObject *Sender);
	void __fastcall LVCustomTextMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall LVCustomTextSelectItem(TObject *Sender, TListItem *Item, bool Selected);

private:	// User declarations
	TDataModule1 *dataModule;
    AuthenticationService *authService;

    std::vector<UnicodeString> customTexts;
public:		// User declarations
	__fastcall TFrCustomText(TComponent* Owner);
    __fastcall TFrCustomText(TComponent* Owner, TDataModule1 *_dataModule, AuthenticationService *_authService);

    void updateTextViewer(int index);
    void resetFrameFields();

    void loadCustomText();
    void addCustomText(const UnicodeString &text);
    void editCustomText(const UnicodeString &text, const UnicodeString &id);
    void deleteCustomText(const UnicodeString &text, const UnicodeString &id);

    bool isNewItem(const UnicodeString &text);

    void executeRequest(const UnicodeString &text);
    void displayErrorMsg();
//    void removeFieldGrid(const UnicodeString &fieldName);
//    void hideColumnGrid(const UnicodeString &fieldName);
//    void setColumnGrid(const UnicodeString &fieldName, const UnicodeString &caption, int width);

};
//---------------------------------------------------------------------------
extern PACKAGE TFrCustomText *FrCustomText;
//---------------------------------------------------------------------------
#endif
