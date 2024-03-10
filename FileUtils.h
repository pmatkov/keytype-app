//---------------------------------------------------------------------------

#ifndef FileUtilsH
#define FileUtilsH

#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.IOUtils.hpp>
#include <System.JSON.hpp>
#include <vcl.h>
#include <vector>
#include <optional>

//---------------------------------------------------------------------------

namespace FileUtils {

		UnicodeString createAbsolutePath(const UnicodeString& filename, bool isfile);
		UnicodeString traverseUpDirTree(const UnicodeString& path, int level);
		std::optional<std::vector<UnicodeString>> getFileNames(const UnicodeString &path, const UnicodeString &fileType);

		TJSONObject* readFromJsonFile(const UnicodeString &path);
		void saveToJsonFile(const UnicodeString &path, const UnicodeString &string);
		std::optional<UnicodeString> readFromTextFile(const UnicodeString &path);
        void saveToTextFile(const UnicodeString &path, const std::vector<UnicodeString> &list);

};
#endif
