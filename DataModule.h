//---------------------------------------------------------------------------

#ifndef DataModuleH
#define DataModuleH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Def.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Pool.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.VCLUI.Wait.hpp>
#include <FireDAC.Phys.MySQL.hpp>
#include <FireDAC.Phys.MySQLDef.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Stan.Param.hpp>

#include <vector>
//---------------------------------------------------------------------------
class TDataModule1 : public TDataModule
{
__published:	// IDE-managed Components
	TFDConnection *MySQLDBConnection;
	TFDTable *TCourses;
	TFDTable *TLessons;
	TDataSource *DCourses;
	TDataSource *DLessons;
	TFDAutoIncField *TCoursesid;
	TStringField *TCoursesname;
	TStringField *TCoursesdescription;
	TIntegerField *TCoursesdifficulty;
	TStringField *TCourseslanguage;
	TFDAutoIncField *TLessonsid;
	TIntegerField *TLessonsidCourses;
	TStringField *TLessonsinstructions;
	TStringField *TLessonscharacters;
	TDateField *TLessonsdateModified;
	TStringField *TLessonsCourseName;
	TFloatField *TLessonsAvgChars;
	TStringField *TLessonsname;
	TIntegerField *TLessonswordCount;
	TIntegerField *TLessonscharCount;
	TStringField *TCoursesgoal;
	TIntegerField *TCoursesgoalValue;
	TDataSource *DUsers;
	TFDTable *TUsers;
	TFDAutoIncField *TUsersid;
	TStringField *TUsersusername;
	TStringField *TUsersname;
	TStringField *TUserssurname;
	TStringField *TUsersemail;
	TIntegerField *TUsersage;
	TBlobField *TUsersprofileImage;
	TDataSource *DLessonResults;
	TFDTable *TLessonResults;
	TFDAutoIncField *TLessonResultsid;
	TIntegerField *TLessonResultsidUser;
	TIntegerField *TLessonResultsidLesson;
	TBooleanField *TLessonResultsresult;
	TDateField *TLessonResultsdate;
	TStringField *TLessonResultslessonName;
	TIntegerField *TLessonResultsidCourse;
	TStringField *TLessonResultslessonGoal;
	TIntegerField *TLessonResultslessonGoalValue;
	TStringField *TUserspassword;
	TBCDField *TLessonResultsspeed;
	TBCDField *TLessonResultsaccuracy;
	void __fastcall TLessonsCalcFields(TDataSet *DataSet);
private:	// User declarations
public:		// User declarations
	__fastcall TDataModule1(TComponent* Owner);
    std::vector<UnicodeString> getColumnNames(TDataSet *DataSet, const UnicodeString &exclude);
    std::vector<std::pair<int, UnicodeString>> getColumnValues(TDataSet *DataSet, const UnicodeString &columnName);
   	std::vector<std::pair<int, UnicodeString>> getColumnValues(TDataSet *DataSet,  const UnicodeString &idName, const UnicodeString &columnName, int index);
    UnicodeString getColumnValue(TDataSet *DataSet, const UnicodeString &columnName, int index);
    std::vector<UnicodeString> getStringsFromColumnValues(const std::vector<std::pair<int, UnicodeString>> &pairs);
};
//---------------------------------------------------------------------------
extern PACKAGE TDataModule1 *DataModule1;
//---------------------------------------------------------------------------
#endif
