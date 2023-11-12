//---------------------------------------------------------------------------

#include "FileUtils.h"
#include <cwctype>

//---------------------------------------------------------------------------
#pragma hdrstop
#pragma package(smart_init)

UnicodeString FileUtils::createFilePath(const UnicodeString& relPath) {

	UnicodeString projectDir = "KeyType";
	UnicodeString exePath = ExtractFilePath(Application->ExeName);
	int position = exePath.Pos(projectDir);
	exePath = exePath.Delete(position + projectDir.Length() + 1, exePath.Length() - position + 1);

	return exePath + relPath;
}

UnicodeString FileUtils::moveUpDirTree(const UnicodeString& path, int level) {

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
