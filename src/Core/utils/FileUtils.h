//---------------------------------------------------------------------------

#ifndef FileUtilsH
#define FileUtilsH

#include <System.IOUtils.hpp>
#include <vcl.h>
#include <vector>
#include <optional>

#define DEF_LEVEL 2

//---------------------------------------------------------------------------

namespace FileUtils {

	UnicodeString getProjectDirPath(int level = DEF_LEVEL);
	UnicodeString createProjectSubDirPath(const UnicodeString& subDirName, int level = DEF_LEVEL);
	UnicodeString createStepUpDirPath(const UnicodeString& path, int level);
	void createDirectory(const UnicodeString& path);

    std::optional<std::vector<UnicodeString>> getFiles(const UnicodeString &path, const UnicodeString &fileType);
    UnicodeString getFileSize(const UnicodeString &path);
    UnicodeString getFileAge(const UnicodeString &path);

    std::optional<UnicodeString> readFromTextFile(const UnicodeString &path);
    std::optional<std::vector<UnicodeString>> readFromTextFileByLine(const UnicodeString &path);
    void saveToTextFile(const UnicodeString &path, const std::vector<UnicodeString> &strings, bool append = false);

};
#endif
