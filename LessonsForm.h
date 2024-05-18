//---------------------------------------------------------------------------

#ifndef LessonsFormH
#define LessonsFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>

#include "CoursesFrame.h"
#include "LessonsFrame.h"
#include "DataModule.h"
#include <Vcl.DBCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Mask.hpp>

//---------------------------------------------------------------------------
class TFLessons : public TForm
{
__published:	// IDE-managed Components
	TButton *BtClose;
	TPageControl *PCLessons;
	TTabSheet *TSCourses;
	TTabSheet *TSLessons;
private:	// User declarations
	std::unique_ptr<TFrCourses> FrCourses;
	std::unique_ptr<TFrLessons> FrLessons;
    TDataModule1 *dataModule;
public:		// User declarations
	__fastcall TFLessons(TComponent* Owner);
    __fastcall TFLessons(TComponent* Owner, TDataModule1 *_dataModule);
};
//---------------------------------------------------------------------------
extern PACKAGE TFLessons *FLessons;
//---------------------------------------------------------------------------
#endif
