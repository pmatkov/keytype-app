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
#include "EFileSizeExceededException.h"

//---------------------------------------------------------------------------

class FileUtils {

	public:
		static UnicodeString createAbsolutePath(const UnicodeString& filename, bool isfile);
		static UnicodeString traverseUpDirTree(const UnicodeString& path, int level);
		static std::optional<std::vector<UnicodeString>> getFileNames(const UnicodeString &path, const UnicodeString &fileType);

		static TJSONObject* readFromJsonFile(const UnicodeString &path);
		static void saveToJsonFile(const UnicodeString &path, const UnicodeString &string);
		static std::optional<UnicodeString> readFromTextFile(const UnicodeString &path);
        static void saveToTextFile(const UnicodeString &path, const std::vector<UnicodeString> &list);

};
#endif
