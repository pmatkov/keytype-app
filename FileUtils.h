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

    bool checkFileExistance(const UnicodeString& filePath);
    std::optional<std::vector<UnicodeString>> getFileNames(const UnicodeString &path, const UnicodeString &fileType);

    std::optional<UnicodeString> readFromTextFile(const UnicodeString &path);
    void saveToTextFile(const UnicodeString &path, const std::vector<UnicodeString> &list);
};
#endif
