//---------------------------------------------------------------------------

#ifndef FileUtilsH
#define FileUtilsH

#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.IOUtils.hpp>
#include <System.JSON.hpp>
#include <vcl.h>
#include "EFileSizeExceededException.h"

//---------------------------------------------------------------------------

class FileUtils {

	public:
		static UnicodeString createAbsolutePath(const UnicodeString& filename, bool isfile);
		static UnicodeString traverseUpDirTree(const UnicodeString& path, int level);

		static void checkFileSize(const UnicodeString& path);
		static bool createFile(const UnicodeString &path);
		static TJSONObject* readJsonFromFile(const UnicodeString &path);
		static void saveJsonToFile(const UnicodeString &path, const UnicodeString &string);

};
#endif
