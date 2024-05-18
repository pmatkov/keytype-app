//---------------------------------------------------------------------------

#include <vcl.h>

#include "LessonsForm.h"
#include "Logger.h"
#include "UIUtils.h"
#include "ENullPointerException.h"
//---------------------------------------------------------------------------
#pragma hdrstop
#pragma package(smart_init)
#pragma link "CoursesFrame"
#pragma link "LessonsFrame"
#pragma resource "*.dfm"
TFLessons *FLessons;
//---------------------------------------------------------------------------
__fastcall TFLessons::TFLessons(TComponent* Owner) : TForm(Owner) {}

__fastcall TFLessons::TFLessons(TComponent* Owner, TDataModule1 *_dataModule) : TForm(Owner)
{

    if (_dataModule) {

    	dataModule = _dataModule;

        FrCourses = UIUtils::createFrame<TFrCourses>(TSCourses, dataModule);
        FrLessons = UIUtils::createFrame<TFrLessons>(TSLessons, dataModule);

        UIUtils::setFrameVisibility<TFrCourses>(FrCourses, true);
        UIUtils::setFrameVisibility<TFrLessons>(FrLessons, true);

       	LOGGER(LogLevel::Debug, "Created form lessons");
    }
    else {
        throw CustomExceptions::ENullPointerException();
    }

}




