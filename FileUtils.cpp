//---------------------------------------------------------------------------
#include <cwctype>
#include <map>
#include <System.IOUtils.hpp>

#include "FileUtils.h"
#include "TextUtils.h"
#include "CryptoUtils.h"
#include "Logger.h"
#include "EDirNotFoundException.h"
#include "EFileNotFoundException.h"

//#define TEST_GET_FILES
#define PROJECT_DIR "KeyType"

//---------------------------------------------------------------------------
#pragma hdrstop
#pragma package(smart_init)

namespace FileUtils {

    // create absolute path from relative path

    UnicodeString createAbsolutePath(const UnicodeString& relPath, bool isFile) {

        UnicodeString projectExePath = ExtractFilePath(Application->ExeName);
        int projectDirStartIndex = projectExePath.Pos(PROJECT_DIR);
        int projectDirLength = sizeof(PROJECT_DIR);

        UnicodeString projectDirPath = projectExePath.Delete(projectDirStartIndex + projectDirLength, projectExePath.Length() - projectDirStartIndex - projectDirLength + 1);
        UnicodeString absPath = projectDirPath + relPath;

        return isFile ? absPath : absPath + "\\";
    }

    UnicodeString traverseUpDirTree(const UnicodeString& path, int level) {

        int pos = path.Length();
        bool active = false;

        while (pos > 1 && level) {

            if (!active && isalpha(path[pos])) {
                active = true;
            }
            if (active && path[pos] == L'\\') {
                level--;
            }
            if (level) {
                pos--;
            }
        }

        UnicodeString newPath = path;

        if (!level) {
            newPath.Delete(pos + 1, path.Length() - pos);
        }

        return newPath;
    }


    // get list of files in a directory

    std::optional<std::vector<UnicodeString>> getFileNames(const UnicodeString &path, const UnicodeString &fileType) {

        #ifdef TEST_GET_FILES
        return std::make_optional(std::vector<UnicodeString>{"archive_2024-03-11_02.zip", "archive_2024-03-14_02.zip", "archive_2024-03-10_03.zip"});

        #else

        if (TDirectory::Exists(path)) {

                std::vector<UnicodeString> filenames;
                TSearchRec searchRec;

                if (FindFirst(path + "*." + fileType, faAnyFile, searchRec) == 0) {

                    do {
                        UnicodeString filename = searchRec.Name;

                        if (TFile::GetSize(path + filename))
                            filenames.push_back(filename);
                        else
                            continue;

                    } while (FindNext(searchRec) == 0);

                    FindClose(searchRec);

                    return filenames;
                }
            }
         else {
            throw CustomExceptions::EDirNotFoundException();
         }
         LOGGER(LogLevel::Debug, "Retrieved list of files");
         return std::nullopt;
         #endif
    }

    UnicodeString getFileSize(const UnicodeString &path) {

      __int64 fileSize = TFile::GetSize(path);

      return fileSize > 1000000 ? FormatFloat("0.00", fileSize/ 1000000.0) + " MB" : FormatFloat("0.00", fileSize/ 1000.0) + " KB";

	}

    UnicodeString getFileAge(const UnicodeString &path) {

      std::unique_ptr<TDateTime> timeDate = std::make_unique<TDateTime>();
      FileAge(path, *timeDate, true);

      return DateTimeToStr(*timeDate);

	}

    std::optional<UnicodeString> readFromTextFile(const UnicodeString &path) {

        UnicodeString filecontents;

        std::unique_ptr<TStreamReader> reader;

        if (FileExists(path))  {

            try {

                reader = std::make_unique<TStreamReader>(path, TEncoding::UTF8);
                filecontents = reader->ReadToEnd();
            }
            catch (const Exception &ex)	{

                ShowMessage("Error reading from file");
                LOGGER(LogLevel::Error, "Error reading from file: " + path);
            }
       }
       else {
           throw CustomExceptions::EFileNotFoundException();
       }

       if (!filecontents.IsEmpty())  {
       		LOGGER(LogLevel::Debug, "Read from file: " + path);
            return filecontents;
       }
       else {
            return std::nullopt;
       }
    }

std::optional<std::vector<UnicodeString>> readFromTextFileByLine(const UnicodeString &path) {

    std::unique_ptr<TStreamReader> reader;
    std::vector<UnicodeString> lines;

    if (FileExists(path)) {
        try {
            reader = std::make_unique<TStreamReader>(path, TEncoding::UTF8);
            UnicodeString line;

            while (!reader->EndOfStream) {
                line = reader->ReadLine();

                if (!line.IsEmpty()) {
                	line = CryptoUtils::decryptStringAES(line);
                    lines.push_back(line);
                }
            }
        } catch (const Exception &ex) {
            ShowMessage("Error reading from file");
            LOGGER(LogLevel::Error, "Error reading from file: " + path);
            return std::nullopt;
        }
    } else {
        throw CustomExceptions::EFileNotFoundException();
    }

    if (!lines.empty()) {
        LOGGER(LogLevel::Debug, "Read from file: " + path);
        return lines;
    } else {
        return std::nullopt;
    }
}


    void saveToTextFile(const UnicodeString &path, const std::vector<UnicodeString> &strings, bool append) {

        std::unique_ptr<TStreamWriter> writer;

        try {

            writer = std::make_unique<TStreamWriter>(path, append, TEncoding::UTF8, 1024);

            for (const UnicodeString &str: strings){
                writer->WriteLine(str);
            }

        }
        catch (Exception &ex)	{

            ShowMessage("Error writing to file");
            LOGGER(LogLevel::Error, "Error writing to file: " + path);
        }

    }

}

