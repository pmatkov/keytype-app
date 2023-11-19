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

	UnicodeString projectDir = PROJECT_DIR;
	UnicodeString exePath = ExtractFilePath(Application->ExeName);
	int dirPosition = exePath.Pos(projectDir);

	UnicodeString projectPath = exePath.Delete(dirPosition + projectDir.Length() + 1, exePath.Length() - dirPosition + 1);

	if (isfile) {
		return projectPath + relPath;
	}
	else {
		return projectPath + relPath + "\\";
	}
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

void FileUtils::checkFileSize(const UnicodeString& path) {

	 if (FileExists(path)) {

		int size = TFile::GetSize(path);

		if (size > MAX_FILE_SIZE) {
			throw EFileSizeExceededException(size, MAX_FILE_SIZE);
		}
    }

}

bool FileUtils::createFile(const UnicodeString &relPath) {

	UnicodeString path = createAbsolutePath(relPath, true);

	if (!FileExists(path))  {

		TFileStream* fileStream = new TFileStream(path, fmCreate);

		delete fileStream;

		return true;
	}
	else {
		return false;
    }
}


 TJSONObject* FileUtils::readJsonFromFile(const UnicodeString &relPath) {

	UnicodeString path = createAbsolutePath(relPath, true);

	if (ExtractFileExt(path).Compare(".json") == 0 && FileExists(path))  {

		try {

			TStreamReader *reader = new TStreamReader(path, TEncoding::UTF8);

			UnicodeString jsonString = reader->ReadToEnd();
			delete reader;

			TJSONObject *jsonObject = (TJSONObject*) (TJSONObject::ParseJSONValue(jsonString));

			if (jsonObject) {
				return jsonObject;
			}

		} catch (const Exception &ex) {
			ShowMessage("Error reading file: " + path);
		}
	}

	return NULL;
}

 void FileUtils::saveJsonToFile(const UnicodeString &relPath, const UnicodeString &jsonString) {

	UnicodeString path = createAbsolutePath(relPath, true);

	try {
		TStreamWriter *writer = new TStreamWriter(path, false, TEncoding::UTF8, 1024);

		writer->WriteLine(jsonString);
		delete writer;

	}
	catch (const Exception &ex)	{

		ShowMessage("Error writing to file: " + path);
	}

}
