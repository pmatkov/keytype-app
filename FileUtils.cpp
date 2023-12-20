//---------------------------------------------------------------------------

#include "FileUtils.h"
#include <cwctype>

#define PROJECT_DIR "KeyType"
#define KB 1024
#define MAX_FILE_SIZE 100 * KB

//---------------------------------------------------------------------------
#pragma hdrstop
#pragma package(smart_init)

UnicodeString FileUtils::getAbsolutePath(const UnicodeString& relPath, bool isFile) {

	UnicodeString exePath = ExtractFilePath(Application->ExeName);
	int pos = exePath.Pos(PROJECT_DIR);
	int len = sizeof(PROJECT_DIR) - 1;

	UnicodeString projectDirPath = exePath.Delete(pos + len + 1, exePath.Length() - pos + 1);
	UnicodeString absPath = projectDirPath + relPath;

    return isFile ? absPath : absPath + "\\";
}

UnicodeString FileUtils::traverseUpDirTree(const UnicodeString& path, int level) {

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


std::optional<std::vector<UnicodeString>> FileUtils::getFileNames(const UnicodeString &path) {


	if (TDirectory::Exists(path)) {

		std::vector<UnicodeString> filenames;
		TSearchRec searchRec;

		if (FindFirst(path + "*.txt", faAnyFile, searchRec) == 0) {

			do {
				UnicodeString filename = searchRec.Name;

				if (TFile::GetSize(path + filename) < MAX_FILE_SIZE)
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


 TJSONObject* FileUtils::readFromJsonFile(const UnicodeString &path) {

    std::unique_ptr<TStreamReader> reader;

    if (ExtractFileExt(path).Compare(".json") == 0 && FileExists(path))  {

        try {

            reader = std::make_unique<TStreamReader>(path, TEncoding::UTF8);
            UnicodeString jsonString = reader->ReadToEnd();

            TJSONObject *jsonObject = (TJSONObject*) (TJSONObject::ParseJSONValue(jsonString));

            if (jsonObject) {
                return jsonObject;
            }

        } catch (const Exception &ex) {
            ShowMessage("Error reading from file: " + path);
        }
    }

	return nullptr;
}

 void FileUtils::saveToJsonFile(const UnicodeString &path, const UnicodeString &string) {

	std::unique_ptr<TStreamWriter> writer;

    try {

        writer = std::make_unique<TStreamWriter>(path, false, TEncoding::UTF8, 1024);
        writer->WriteLine(string);

    }
    catch (const Exception &ex)	{
        ShowMessage("Error writing to file: " + path);
    }

}


std::optional<UnicodeString> FileUtils::readFromTextFile(const UnicodeString &path) {

	UnicodeString filecontents;

	std::unique_ptr<TStreamReader> reader;

	if (FileExists(path))  {

        try {

            reader = std::make_unique<TStreamReader>(path, TEncoding::UTF8);
            filecontents = reader->ReadToEnd();

        }
        catch (const Exception &ex)	{

            ShowMessage("Error reading from file: " + path);
        }
   }

   if (!filecontents.IsEmpty())  {
        return filecontents;
   }
   else {
		return std::nullopt;
   }

}

void FileUtils::saveToTextFile(const UnicodeString &path, const std::vector<UnicodeString> &list) {

	std::unique_ptr<TStreamWriter> writer;

    try {

        writer = std::make_unique<TStreamWriter>(path, false, TEncoding::UTF8, 1024);

        for (const UnicodeString &string: list){
            writer->WriteLine(string);
        }
    }
    catch (const Exception &ex)	{

        ShowMessage("Error writing to file: " + path);
    }

}
