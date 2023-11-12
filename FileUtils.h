//---------------------------------------------------------------------------

#ifndef FileUtilsH
#define FileUtilsH

#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.IOUtils.hpp>
#include <vcl.h>

//---------------------------------------------------------------------------

class FileUtils {

	public:
		static UnicodeString createFilePath(const UnicodeString& relPath);
		static UnicodeString moveUpDirTree(const UnicodeString& path, int level);

};
#endif
