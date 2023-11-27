//---------------------------------------------------------------------------

#include "FileUtils.h"
#include <cwctype>

#define PROJECT_DIR "KeyType"
#define KB 1024
#define MAX_FILE_SIZE 100 * KB

//---------------------------------------------------------------------------
#pragma hdrstop
#pragma package(smart_init)

UnicodeString FileUtils::createAbsolutePath(const UnicodeString& relPath, bool isfile) {

	UnicodeString path = "";
	UnicodeString exePath = ExtractFilePath(Application->ExeName);
	int dirPosition = exePath.Pos(PROJECT_DIR);
	int len = sizeof(PROJECT_DIR) - 1;

	UnicodeString projectPath = exePath.Delete(dirPosition + len + 1, exePath.Length() - dirPosition + 1);

	path += projectPath + relPath;

	if (!isfile) {
		path += "\\";
	}

	return path;
}

UnicodeString FileUtils::traverseUpDirTree(const UnicodeString& path, int level) {

	UnicodeString pathCopy = path;

	wchar_t delimiter = L'\\';
	int i = pathCopy.Length();
	bool active = false;

	while (i > 1 && level) {

		if (!active && isalpha(pathCopy[i])) {
			active = true;
		}
		if (active && pathCopy[i] == delimiter) {
			level--;
		}
		if (level) {
			i--;
		}
	}

	if (!level) {
		  pathCopy.Delete(i + 1, pathCopy.Length() - i);
	}

	return pathCopy;

}


std::optional<std::vector<UnicodeString>> FileUtils::getFileNamesInDir(const UnicodeString &path) {

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

// izbaciti?
void FileUtils::checkFileSize(const UnicodeString& path) {

	 if (FileExists(path)) {

		int size = TFile::GetSize(path);

		if (size > MAX_FILE_SIZE) {
			throw EFileSizeExceededException(size, MAX_FILE_SIZE);
		}
    }

}


 TJSONObject* FileUtils::readFromJsonFile(const UnicodeString &relPath) {

	UnicodeString path = createAbsolutePath(relPath, true);

	TStreamReader *reader = NULL;

	try {

		if (ExtractFileExt(path).Compare(".json") == 0 && FileExists(path))  {

			try {

				reader = new TStreamReader(path, TEncoding::UTF8);
				UnicodeString jsonString = reader->ReadToEnd();

				TJSONObject *jsonObject = (TJSONObject*) (TJSONObject::ParseJSONValue(jsonString));

				if (jsonObject) {
					return jsonObject;
				}

			} catch (const Exception &ex) {
				ShowMessage("Error reading from file: " + path);
			}
		}
	}
	__finally {
		delete reader;
	}

	return nullptr;
}

 void FileUtils::saveToJsonFile(const UnicodeString &relPath, const UnicodeString &jsonString) {

	UnicodeString path = createAbsolutePath(relPath, true);

	TStreamWriter *writer = NULL;

	try {

		try {

			writer = new TStreamWriter(path, false, TEncoding::UTF8, 1024);
			writer->WriteLine(jsonString);

		}
		catch (const Exception &ex)	{

			ShowMessage("Error writing to file: " + path);
		}
	}
	__finally {
		delete writer;
	}

}


std::optional<UnicodeString> FileUtils::readFromTextFile(const UnicodeString &path) {

	UnicodeString fileContents;

	TStreamReader *reader = NULL;

	if (FileExists(path))  {

		try {

			try {

				TStreamReader *reader = new TStreamReader(path, TEncoding::UTF8);
				fileContents = reader->ReadToEnd();

			}
			catch (const Exception &ex)	{

				ShowMessage("Error reading from file: " + path);
			}
		}
		__finally
		{
			delete reader;
		}

   }

   if (!fileContents.IsEmpty())  {
        return fileContents;
   }
   else {
		return std::nullopt;
   }

}
