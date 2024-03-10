//---------------------------------------------------------------------------

#include "FileUtils.h"
#include "Logger.h"
#include <cwctype>

#define PROJECT_DIR "KeyType"
#define KB 1024

//---------------------------------------------------------------------------
#pragma hdrstop
#pragma package(smart_init)

namespace FileUtils {

    // create absolute file or dir path (relative path starts at <project root>)

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


    // get directory contents

    std::optional<std::vector<UnicodeString>> getFileNames(const UnicodeString &path, const UnicodeString &fileType) {

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

        return std::nullopt;
    }


     TJSONObject* readFromJsonFile(const UnicodeString &path) {

        std::unique_ptr<TStreamReader> reader;

        if (ExtractFileExt(path).Compare(".json") == 0 && FileExists(path))  {

            try {

                reader = std::make_unique<TStreamReader>(path, TEncoding::UTF8);
                UnicodeString jsonString = reader->ReadToEnd();

                TJSONObject *jsonObject = (TJSONObject*) (TJSONObject::ParseJSONValue(jsonString));

                if (jsonObject) {
                	LOGGER(LogLevel::Debug, "Read from file: " + path);
                    return jsonObject;
                }

            } catch (const Exception &ex) {
                ShowMessage("Error reading from file");
                LOGGER(LogLevel::Error, "Error reading from file: " + path);
            }
        }

        return nullptr;
    }

     void saveToJsonFile(const UnicodeString &path, const UnicodeString &string) {

        std::unique_ptr<TStreamWriter> writer;

        try {

            writer = std::make_unique<TStreamWriter>(path, false, TEncoding::UTF8, 1024);
            writer->WriteLine(string);
            LOGGER(LogLevel::Debug, "Saved to file: " + path);

        }
        catch (const Exception &ex)	{
            ShowMessage("Error writing to file");
            LOGGER(LogLevel::Error, "Error writing to file: " + path);
        }

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

       if (!filecontents.IsEmpty())  {
       		LOGGER(LogLevel::Debug, "Read from file: " + path);
            return filecontents;
       }
       else {
            return std::nullopt;
       }

    }

    void saveToTextFile(const UnicodeString &path, const std::vector<UnicodeString> &list) {

        std::unique_ptr<TStreamWriter> writer;

        try {

            writer = std::make_unique<TStreamWriter>(path, false, TEncoding::UTF8, 1024);

            for (const UnicodeString &string: list){
                writer->WriteLine(string);
            }

            LOGGER(LogLevel::Debug, "Saved to file: " + path);
        }
        catch (Exception &ex)	{

            ShowMessage("Error writing to file");
            LOGGER(LogLevel::Error, "Error writing to file: " + path);
        }

    }
}

