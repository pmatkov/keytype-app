//---------------------------------------------------------------------------

#ifndef LessonResultsFormH
#define LessonResultsFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>

#include "DataModule.h"
#include <Vcl.DBCtrls.hpp>
#include "frxClass.hpp"
#include "frxDBSet.hpp"
#include "frxExportBaseDialog.hpp"
#include "frxExportPDF.hpp"
#include "frxExportRTF.hpp"

//---------------------------------------------------------------------------
class TFLessonResults : public TForm
{
__published:	// IDE-managed Components
	TDBGrid *DBGridLessonResults;
	TDBGrid *DBUsers;
	TDBImage *DBImage;
	TfrxReport *frxReport;
	TfrxDBDataset *frxUser;
	TfrxDBDataset *frxLessonResult;
	TButton *BtViewReport;
	TfrxPDFExport *frxPDFExport;
	TfrxRTFExport *frxRTFExport;
	TButton *BtExportRtf;
	TButton *BtExportPdf;
	void __fastcall BtViewReportClick(TObject *Sender);
	void __fastcall BtExportPdfClick(TObject *Sender);
	void __fastcall BtExportRtfClick(TObject *Sender);

private:	// User declarations
  	TDataModule1 *dataModule;
public:		// User declarations
	__fastcall TFLessonResults(TComponent* Owner);
    __fastcall TFLessonResults(TComponent* Owner, TDataModule1 *_dataModule);
};
//---------------------------------------------------------------------------
extern PACKAGE TFLessonResults *FLessonResults;
//---------------------------------------------------------------------------
#endif
