//---------------------------------------------------------------------------

#ifndef PracticeFormH
#define PracticeFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <memory>
#include <vector>

//---------------------------------------------------------------------------
class TFPractice : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PCSourceText;
	TTabSheet *TSGeneratedText;
	TTabSheet *TSCustomText;
	TTabSheet *TSExternalSources;
	TLabel *LTextSourceInfo;
	TButton *AButton;
	TButton *CButton;

	TRadioGroup *RGGeneratedText;
	TGroupBox *GBCharacters;
	TGroupBox *GBWords;
	TToolBar *LettersToolbar;
	TCheckBox *CBSelectAll;
	TCheckBox *CBNumbers;
	TCheckBox *CBPunctuation;
	TBevel *Bevel1;
	TCheckBox *CBCapitalLetters;

	void __fastcall CButtonClick(TObject *Sender);
	void __fastcall RGGeneratedTextClick(TObject *Sender);
	void __fastcall CBSelectAllClick(TObject *Sender);

private:	// User declarations

//	std::vector<std::unique_ptr<TToolButton>> buttons;
	std::vector<TToolButton*> buttons;

public:		// User declarations
	__fastcall TFPractice(TComponent* Owner);
	void __fastcall updateGroupBoxState();
	void changeChildControlsStatus(TWinControl* parentControl, Boolean status);
	const std::vector<TToolButton*>& getButtons() const;
//	const std::vector<std::unique_ptr<TToolButton>>& getButtons() const;

};
//---------------------------------------------------------------------------
extern PACKAGE TFPractice *FPractice;
//---------------------------------------------------------------------------
#endif
