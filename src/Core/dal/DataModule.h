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
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include "uTPLb_BaseNonVisualComponent.hpp"
#include "uTPLb_Codec.hpp"
#include "uTPLb_CryptographicLibrary.hpp"
#include "uTPLb_Signatory.hpp"
#include <System.SysUtils.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.ObjectScope.hpp>
#include <REST.Client.hpp>
#include <REST.Response.Adapter.hpp>
#include <REST.Types.hpp>
#include <REST.Authenticator.Basic.hpp>
#include <IdUDPBase.hpp>
#include <IdUDPClient.hpp>

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
	TDateField *TLessonResultsdate;
	TStringField *TLessonResultslessonName;
	TIntegerField *TLessonResultsidCourse;
	TStringField *TLessonResultslessonGoal;
	TIntegerField *TLessonResultslessonGoalValue;
	TStringField *TUserspassword;
	TBCDField *TLessonResultsspeed;
	TBCDField *TLessonResultsaccuracy;
	TStringField *TLessonResultsresult;
	TIdTCPClient *IdTCPClient;
	TIntegerField *TLessonResultsduration;
	TStringField *TLessonResultsdurationHMS;
	TDataSource *DKeyStatistics;
	TFDTable *TKeyStatistics;
	TFDAutoIncField *TKeyStatisticsid;
	TIntegerField *TKeyStatisticsidLessonResults;
	TStringField *TKeyStatisticskey;
	TIntegerField *TKeyStatisticscorrect;
	TIntegerField *TKeyStatisticsmistake;
	TRESTClient *RESTClient;
	TRESTRequest *RESTRequest;
	TRESTResponse *RESTResponse;
	TRESTResponseDataSetAdapter *RESTResponseDataSetAdapter;
	TFDMemTable *FDMemTable;
	TDataSource *DWebService;
	TIdUDPClient *IdUDPClient;
	TStringField *TUsersrole;
	TFDPhysMySQLDriverLink *FDPhysMySQLDriverLink;
	void __fastcall TLessonsCalcFields(TDataSet *DataSet);
	void __fastcall TLessonResultsCalcFields(TDataSet *DataSet);
private:	// User declarations
public:		// User declarations
	__fastcall TDataModule1(TComponent* Owner);
    std::vector<UnicodeString> getColumnNames(TDataSet *DataSet, const UnicodeString &exclude);
    std::vector<std::pair<int, UnicodeString>> getColumnValues(TDataSet *DataSet, const UnicodeString &columnName);
   	std::vector<std::pair<int, UnicodeString>> getColumnValues(TDataSet *DataSet,  const UnicodeString &idName, const UnicodeString &columnName, int index);
    UnicodeString getColumnValue(TDataSet *DataSet, const UnicodeString &columnName, int index);
    std::vector<UnicodeString> getStringsFromColumnValues(const std::vector<std::pair<int, UnicodeString>> &pairs);

    UnicodeString generateText(const UnicodeString &letters, bool useNumbers, bool useUppercase,  bool usePunctuation, int minTokens, int maxTokens);
    bool convertWordList(const UnicodeString& filePath);
    UnicodeString translateKey(const UnicodeString &key);
};
//---------------------------------------------------------------------------
extern PACKAGE TDataModule1 *DataModule1;
//---------------------------------------------------------------------------
#endif
