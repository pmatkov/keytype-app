//---------------------------------------------------------------------------

#pragma hdrstop

#include "Achievement.h"
#include "AchievementsUtils.h"
#include "CryptoUtils.h"
#include "EnumUtils.h"
#include "Logger.h"

#include <memory>
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace AchievementsUtils {

    void saveToFile(const AchievementsHeader &header, const std::vector<AchievementsRecord> &records, const UnicodeString &path) {

    	std::unique_ptr<TFileStream> fileStream;

        try {

            fileStream = std::make_unique<TFileStream>(path + ".acm", fmCreate);
            fileStream->Write(&header, sizeof(AchievementsHeader));

            for (const AchievementsRecord &record: records) {

                fileStream->Write(&record, sizeof(AchievementsRecord));
            }

            LOGGER(LogLevel::Debug, "Saved to file: " + path);
        }
        catch (Exception &ex)	{

            ShowMessage("Error writing to file");
            LOGGER(LogLevel::Error, "Error writing to file: " + path);
        }

    }

    std::vector<AchievementsRecord> readFromFile(const UnicodeString &path) {

        AchievementsHeader header;
        std::vector<AchievementsRecord> records;

        std::unique_ptr<TFileStream> fileStream;

        if (FileExists(path + ".acm")) {

            try {

            	fileStream = std::make_unique<TFileStream>(path + ".acm", fmOpenRead);
                fileStream->Read(&header, sizeof(AchievementsHeader));

                if (header.getHashValue() != CryptoUtils::generateSHA512Hash(header)) {

                    ShowMessage(header.getHashValue() + " " + CryptoUtils::generateSHA512Hash(UnicodeString(header)) + " Invalid hash value");
                    LOGGER(LogLevel::Debug, "Invalid hash value");
                    return records;
                }

                for (int i = 0; i < header.getRecordCount(); i++) {

                    AchievementsRecord record;

                    fileStream->Read(&record, sizeof(AchievementsRecord));
                    records.push_back(record);
                }

                LOGGER(LogLevel::Debug, "Read from file: " + path);
           }
           catch (const Exception &ex)	{

                ShowMessage("Error reading from file");
                LOGGER(LogLevel::Error, "Error reading from file: " + path);
            }
       }

       return records;

    }

    std::vector<AchievementsRecord> filterAchievements(const std::vector<AchievementsRecord> &records, int idUser, AchievementType type) {

    	std::vector<AchievementsRecord> filteredRecords;
        bool addRecord;

    	for (const AchievementsRecord &record: records) {

            addRecord = false;

            if (idUser) {
              if (record.getIdUser() == idUser) {
              	addRecord = true;
              }
            }
            else if (type != AchievementType::Unknown) {
                if (EnumUtils::enumToString<AchievementType>(Achievement::getAchievementTypeStrings(), type) == record.getTitle()) {
					addRecord = true;
                }
            }
            else if (idUser && type != AchievementType::Unknown) {
                 if (record.getIdUser() == idUser && (EnumUtils::enumToString<AchievementType>(Achievement::getAchievementTypeStrings(), type) == record.getTitle())) {
					addRecord = true;
                }
            }
            if (addRecord) {
               filteredRecords.push_back(record);
            }
        }

        return  filteredRecords;
    }
}
