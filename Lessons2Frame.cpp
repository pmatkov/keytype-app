//---------------------------------------------------------------------------

#pragma hdrstop
#undef UNICODE
#define UNICODE

#include "Lessons2Frame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "OptionsFrame"
#pragma link "PracticeFrame"
#pragma link "TypingStatsFrame"
#pragma link "TypingTextFrame"
#pragma resource "*.dfm"

#include "UIUtils.h"
#include "TextUtils.h"
#include "EnumUtils.h"
#include "Generator.h"
#include "Logger.h"
#include "ENullPointerException.h"
#include "Statistics\\UserStatistics.h"

TFrLessons2 *FrLessons2;
//---------------------------------------------------------------------------
__fastcall TFrLessons2::TFrLessons2(TComponent* Owner)
	: TFrame(Owner)   {}

 __fastcall TFrLessons2::TFrLessons2(TComponent* Owner, Parser* _parser, MainSession *_mainSession, TypingSession *_typingSession, AuthenticationService *_authService,\
 	 TDataModule1 *_dataModule) : TFrame(Owner) {
	if (_parser && _mainSession && _typingSession && _authService && _dataModule) {

       parser = _parser;
       mainSession = _mainSession;
	   typingSession = _typingSession;
       dataModule = _dataModule;
       authService = _authService;

       FrTypingStats->setMainSession(mainSession);
       FrTypingStats->setTypingSession(typingSession);
       FrTypingStats->hideStatsItems();

       FrTypingText->setMainSession(mainSession);
       FrTypingText->setTypingSession(typingSession);
       FrTypingText->setParser(parser);
       FrTypingText->setFrameTypingStats(FrTypingStats);

       coursesValues = dataModule->getColumnValues(dataModule->TCourses, "name");
       std::vector<UnicodeString> courseStringValues = dataModule->getStringsFromColumnValues(coursesValues);

       if (mainSession->getAppSettings().getLanguage() == Language::English) {
       		courseStringValues.insert(courseStringValues.begin(), "-select course-");
        }
        else if (mainSession->getAppSettings().getLanguage() == Language::Croatian) {
        	courseStringValues.insert(courseStringValues.begin(), "-odaberi kurs-");
        }

       UIUtils::setComboBoxItems(CBSelectCourse, courseStringValues, 0);

       FrTypingText->OnTypingComplete = FrTypingTextTypingComplete;

       LOGGER(LogLevel::Debug, "Lessons2 frame displayed");
	}
    else {
        throw CustomExceptions::ENullPointerException();
    }
}

void __fastcall TFrLessons2::CBSelectCourseChange(TObject *Sender)
{
   	int index  = -1;
    if (CBSelectCourse->ItemIndex > 0) {
    	index = coursesValues[CBSelectCourse->ItemIndex-1].first;
    }

    dataModule->TCourses->Locate("id", index, TLocateOptions());

    lessonsValues = dataModule->getColumnValues(dataModule->TLessons, "idCourses", "name", index);
    std::vector<UnicodeString> lessonStringValues = dataModule->getStringsFromColumnValues(lessonsValues);

    if (mainSession->getAppSettings().getLanguage() == Language::English) {
    	lessonStringValues.insert(lessonStringValues.begin(), "-select lesson-");
    }
    else if (mainSession->getAppSettings().getLanguage() == Language::Croatian) {
        lessonStringValues.insert(lessonStringValues.begin(), "-odaberi lekciju-");
    }

    UIUtils::setComboBoxItems(CBSelectLesson, lessonStringValues, 0);

    UIUtils::selectComboBoxItem(CBSelectLesson, 0);
    hideInterfaceValues();
    LLessonResult->Visible = false;
    LLessonResultDisplay->Caption = "";
}

void __fastcall TFrLessons2::CBSelectLessonChange(TObject *Sender)
{

    if (CBSelectLesson->ItemIndex > 0) {

    	int index = lessonsValues[CBSelectLesson->ItemIndex-1].first;
        int indexCourses = coursesValues[CBSelectCourse->ItemIndex-1].first;

        typingSession->setCharCount(StrToInt(dataModule->getColumnValue(dataModule->TLessons, "charCount", index)));
        typingSession->setWordCount(StrToInt(dataModule->getColumnValue(dataModule->TLessons, "wordCount", index)));
        typingSession->setLessonGoal(EnumUtils::stringToEnum<LessonGoal>(typingSession->getLessonGoalStrings(), dataModule->getColumnValue(dataModule->TCourses, "goal", indexCourses)));
        typingSession->setGoalValue(StrToInt(dataModule->getColumnValue(dataModule->TCourses, "goalValue", indexCourses)));
        typingSession->setDifficulty(StrToInt(dataModule->getColumnValue(dataModule->TCourses, "difficulty", indexCourses)));

        LCharsDisplay->Caption = IntToStr(typingSession->getCharCount());
        LWordsDisplay->Caption = IntToStr(typingSession->getWordCount());
        UnicodeString goal = EnumUtils::enumToString(typingSession->getLessonGoalStrings(), typingSession->getLessonGoal());
        LGoalDisplay->Caption = EnumUtils::enumToString(typingSession->getLessonGoalStrings(), typingSession->getLessonGoal()) +
            " " + IntToStr(typingSession->getGoalValue()) + (goal == "speed" ? " WPM" : " %");
        LDifficultyDisplay->Caption = IntToStr(typingSession->getDifficulty());

        dataModule->TCourses->Locate("id", indexCourses, TLocateOptions());

        MInstructions->Clear();
        MInstructions->Lines->BeginUpdate();
        MInstructions->Lines->Add("Instructions: " + dataModule->getColumnValue(dataModule->TLessons, "instructions", index));
        MInstructions->Lines->EndUpdate();

        LLessonResult->Visible = false;
    	LLessonResultDisplay->Caption = "";

        if (typingSession->getSessionStatus() == SessionStatus::Completed) {

        	if (mainSession->getAppSettings().getLanguage() == Language::English) {
            	BtStartQuit->Caption = "Start";
            }
            else if (mainSession->getAppSettings().getLanguage() == Language::Croatian) {
            	BtStartQuit->Caption = "Pokreni";
            }
            typingSession->setSessionStatus(SessionStatus::Cleared);
            FrTypingText->setTypingStatus(SessionStatus::Cleared);

            FrTypingStats->hideStatsItems();
        }
    }
    else {
         hideInterfaceValues();
    }

}

void TFrLessons2::hideInterfaceValues() {

    LCharsDisplay->Caption = "";
    LWordsDisplay->Caption = "";
    LGoalDisplay->Caption = "";
    LDifficultyDisplay->Caption = "";
    MInstructions->Clear();

    FrTypingText->REText->Text = "";
}


bool TFrLessons2::setTextSource(int index) {

//	UnicodeString textSource = Generator::generateText(dataModule->getColumnValue(dataModule->TLessons, "characters", index), \
//     GeneratorOptions(false, false, false, typingSession->getWordCount(), typingSession->getWordCount()));

	UnicodeString textSource = dataModule->generateText(dataModule->getColumnValue(dataModule->TLessons, "characters", index), \
     false, false, false, typingSession->getWordCount(), typingSession->getWordCount());


     if (!textSource.IsEmpty()) {

        // shorten generated text if longer than lesson char count
     	if (textSource.Length() > typingSession->getCharCount()) {
         	textSource.SetLength(typingSession->getCharCount());
        }

        // set source text
        typingSession->setTextSource(TextSource(textSource));
        return true;
     }

     ShowMessage("Lessson text was not generated. Check connection to the server.");
     return false;
}


void __fastcall TFrLessons2::BtStartQuitClick(TObject *Sender)
{

	if (BtStartQuit->Caption == "Start" || BtStartQuit->Caption == "Pokreni" ||  BtStartQuit->Caption == "Restart" || BtStartQuit->Caption == "Ponovi") {

        // warn if lesson isn't selected

        if (CBSelectLesson->ItemIndex == 0) {

        	if (mainSession->getAppSettings().getLanguage() == Language::English) {
            	ShowMessage("-select lesson-");
            }
            else if (mainSession->getAppSettings().getLanguage() == Language::Croatian) {
                ShowMessage("-odaberi lekciju-");
            }

        }
        else{

        	int index = lessonsValues[CBSelectLesson->ItemIndex-1].first;
        	if (setTextSource(index)) {

                if (mainSession->getAppSettings().getLanguage() == Language::English) {
                   BtStartQuit->Caption = "Quit";
                }
                else if (mainSession->getAppSettings().getLanguage() == Language::Croatian) {
                    BtStartQuit->Caption = "Završi";
                }

                CBSelectCourse->Enabled = false;
                CBSelectLesson->Enabled = false;

                this->SetFocus();

                LLessonResult->Visible = false;
                LLessonResultDisplay->Caption = "";

                typingSession->setSessionStatus(SessionStatus::Initialized);
                FrTypingText->setTypingStatus(SessionStatus::Initialized);
            }

        }
	}
    else if (BtStartQuit->Caption == "Quit" || BtStartQuit->Caption == "Završi" ) {

    	if (mainSession->getAppSettings().getLanguage() == Language::English) {
           BtStartQuit->Caption = "Start";
        }
        else if (mainSession->getAppSettings().getLanguage() == Language::Croatian) {
            BtStartQuit->Caption = "Pokreni";
        }

        CBSelectCourse->Enabled = true;
        CBSelectLesson->Enabled = true;

        LLessonResult->Visible = true;
        LLessonResultDisplay->Font->Color = clRed;
        if (mainSession->getAppSettings().getLanguage() == Language::English) {
           LLessonResultDisplay->Caption = "cancelled";
        }
        else if (mainSession->getAppSettings().getLanguage() == Language::Croatian) {
            LLessonResultDisplay->Caption = " otkazano";
        }

        typingSession->setSessionStatus(SessionStatus::Completed);
        FrTypingText->setTypingStatus(SessionStatus::Completed);
        typingSession->setSessionStatus(SessionStatus::Cleared);
        FrTypingText->setTypingStatus(SessionStatus::Cleared);

        typingSession->resetSessionData();
        parser->resetParserData();

    }
}

void __fastcall TFrLessons2::FrTypingTextTypingComplete(TObject *Sender)
{

    bool passed = false;
    float lessonResult, avgSpeed, accuracy;
    std::map<wchar_t, KeyStatistics> keyStatistics;

    avgSpeed = typingSession->getAvgSpeed();
    accuracy = typingSession->getAccuracy();

    keyStatistics = typingSession->getKeyStatistics();

    if (typingSession->getLessonGoal() == LessonGoal::lSpeed) {
    	lessonResult = avgSpeed;
    }
    else if (typingSession->getLessonGoal() == LessonGoal::lAccuracy) {
        lessonResult = accuracy;
    }

    if (lessonResult >= typingSession->getGoalValue()) {
    	passed = true;
    }

    LLessonResult->Visible = true;
    LLessonResultDisplay->Font->Color =  passed ? TColor(0x8B8B00) : TColor(0x0045FF);

    if (mainSession->getAppSettings().getLanguage() == Language::English) {
        LLessonResultDisplay->Caption = passed ? " passed (" : " failed (";
    }
    else if (mainSession->getAppSettings().getLanguage() == Language::Croatian) {
    	LLessonResultDisplay->Caption = passed ? " položeno (" : " nije položeno (";
    }

    LLessonResultDisplay->Caption += typingSession->getLessonGoal() == LessonGoal::lSpeed ? (FormatFloat("0.00", avgSpeed) + " WPM)") : (FormatFloat("0.00", accuracy) + " %)");

    CBSelectCourse->Enabled = true;
    CBSelectLesson->Enabled = true;

    if (mainSession->getAppSettings().getLanguage() == Language::English) {
        BtStartQuit->Caption = "Restart";
    }
    else if (mainSession->getAppSettings().getLanguage() == Language::Croatian) {
        BtStartQuit->Caption = "Ponovi";
    }

    if (dataModule->TUsers->Locate("username; password", VarArrayOf(OPENARRAY(Variant, (authService->getUser().getUsername(), authService->getUser().getPassword()))), TLocateOptions())) {

        int userID = dataModule->TUsers->FieldByName("id")->AsInteger;
        int lessonID = lessonsValues[CBSelectLesson->ItemIndex-1].first;

        dataModule->TLessonResults->Append();
        dataModule->TLessonResults->FieldByName("idUser")->AsInteger = userID;
        dataModule->TLessonResults->FieldByName("idLesson")->AsInteger = lessonID;
        dataModule->TLessonResults->FieldByName("result")->AsString = passed ? "passed" : "failed";
        dataModule->TLessonResults->FieldByName("speed")->AsFloat = avgSpeed;
        dataModule->TLessonResults->FieldByName("accuracy")->AsFloat = accuracy;
        dataModule->TLessonResults->FieldByName("duration")->AsInteger = typingSession->getElapsedTime();
        dataModule->TLessonResults->FieldByName("date")->AsDateTime = Date();
        dataModule->TLessonResults->Post();

        dataModule->TLessonResults->Last();
        int lastID = dataModule->TLessonResults->FieldByName("ID")->AsInteger;

        for (const std::pair<wchar_t, KeyStatistics>& ks : keyStatistics) {

            wchar_t key = ks.first;
            int correct = ks.second.getCorrect();
 			int mistake = ks.second.getMistake();

            if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z')) {
                 if (std::isalpha(key)) {
                    key = std::tolower(key);

                 }

                dataModule->TKeyStatistics->Append();
                dataModule->TKeyStatistics->FieldByName("idLessonResults")->AsInteger = lastID;
                dataModule->TKeyStatistics->FieldByName("key")->AsString = UnicodeString(key);
                dataModule->TKeyStatistics->FieldByName("correct")->AsInteger = correct;
                dataModule->TKeyStatistics->FieldByName("mistake")->AsInteger = mistake;
                dataModule->TKeyStatistics->Post();
            }
        };

    }

    typingSession->setSessionStatus(SessionStatus::Completed);
    FrTypingText->setTypingStatus(SessionStatus::Completed);

    typingSession->resetSessionData();
    parser->resetParserData();
}

void TFrLessons2::processCharMessages(WPARAM wParam) {

 	FrTypingText->processCharMessages(wParam);

}

void __fastcall TFrLessons2::WndProc(TMessage &Message)
{
	switch (Message.Msg) {
        case WM_CHAR:
			processCharMessages(Message.WParam);
            break;

       	default:
            TFrame::WndProc(Message);
    }
}

