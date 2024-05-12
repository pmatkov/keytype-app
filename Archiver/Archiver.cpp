#include <iostream>
#include <tchar.h>
#include <windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
    std::string command = "";


    for (int i = 1; i < argc; i++) {
        command += argv[i];

        if (i < argc - 1) {
            command += " ";
        }
    }

    if (command.find("tar") == std::string::npos) {
        return 1;
    }
    else if (command.find(".log") == std::string::npos) {
        return 2;
    }

    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    unsigned long returnValue;

    if (!CreateProcess(NULL, const_cast<char*>(command.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        return 3;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    GetExitCodeProcess(pi.hProcess, &returnValue);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);


    return (int)returnValue;

}


