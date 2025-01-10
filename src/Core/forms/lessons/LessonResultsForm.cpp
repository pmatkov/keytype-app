//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LessonResultsForm.h"
#include "UIUtils.h"
#include "FileUtils.h"
#include "Logger.h"
#include "ENullPointerException.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "frxClass"
#pragma link "frxDBSet"
#pragma link "frxExportBaseDialog"
#pragma link "frxExportPDF"
#pragma link "frxExportRTF"
#pragma resource "*.dfm"
TFLessonResults *FLessonResults;
//---------------------------------------------------------------------------
__fastcall TFLessonResults::TFLessonResults(TComponent* Owner) : TForm(Owner) {}

__fastcall TFLessonResults::TFLessonResults(TComponent* Owner, TDataModule1 *_dataModule) : TForm(Owner) {

	if (_dataModule) {
    	dataModule = _dataModule;
		dataModule->TLessons->MasterSource = nullptr;

		UnicodeString path = FileUtils::createProjectSubDirPath("Report");

		frxPDFExport->DefaultPath = path;
		frxRTFExport->DefaultPath = path;

    }
    else {
        throw CustomExceptions::ENullPointerException();
    }
}

void __fastcall TFLessonResults::BtViewReportClick(TObject *Sender)
{
	frxReport->ShowReport();
}

void __fastcall TFLessonResults::BtExportPdfClick(TObject *Sender)
{
	frxReport->PrepareReport();
    frxReport->Export(frxPDFExport);

}

void __fastcall TFLessonResults::BtExportRtfClick(TObject *Sender)
{
   	frxReport->PrepareReport();
    frxReport->Export(frxRTFExport);
}
//---------------------------------------------------------------------------

