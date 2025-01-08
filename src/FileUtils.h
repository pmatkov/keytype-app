//---------------------------------------------------------------------------

#ifndef FileUtilsH
#define FileUtilsH

#include <System.IOUtils.hpp>
#include <vcl.h>
#include <vector>
#include <optional>

//---------------------------------------------------------------------------

namespace FileUtils {

    UnicodeString createAbsolutePath(const UnicodeString& filename, bool isfile);
    UnicodeString traverseUpDirTree(const UnicodeString& path, int level);

    std::optional<std::vector<UnicodeString>> getFiles(const UnicodeString &path, const UnicodeString &fileType);
    UnicodeString getFileSize(const UnicodeString &path);
    UnicodeString getFileAge(const UnicodeString &path);

    std::optional<UnicodeString> readFromTextFile(const UnicodeString &path);
    std::optional<std::vector<UnicodeString>> readFromTextFileByLine(const UnicodeString &path);
    void saveToTextFile(const UnicodeString &path, const std::vector<UnicodeString> &strings, bool append = false);

};
#endif
