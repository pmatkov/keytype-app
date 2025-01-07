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

                    // verify header hash

                    ShowMessage(header.getHashValue() + " " + CryptoUtils::generateSHA512Hash(header) + " Invalid hash value");
                    LOGGER(LogLevel::Error, "Invalid hash value");
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

    	for (const AchievementsRecord &record: records) {

            bool foundMatchingRecord = false;

            // filter by user, achievement type or both

            if (idUser) {
              if (record.getIdUser() == idUser) {
              	foundMatchingRecord = true;
              }
            }
            else if (type != AchievementType::Unknown) {
                if (EnumUtils::enumToString<AchievementType>(Achievement::getAchievementTypeStrings(), type) == record.getTitle()) {
					foundMatchingRecord = true;
                }
            }
            else if (idUser && type != AchievementType::Unknown) {
                 if (record.getIdUser() == idUser && (EnumUtils::enumToString<AchievementType>(Achievement::getAchievementTypeStrings(), type) == record.getTitle())) {
					foundMatchingRecord = true;
                }
            }

            if (foundMatchingRecord) {
               filteredRecords.push_back(record);
            }
        }

        return  filteredRecords;
    }
}
