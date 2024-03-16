#include <iostream>
#include <tchar.h>
#include <windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
    std::string command;

    for (int i = 1; i < argc; ++i) {
        command += argv[i];

        if (i < argc - 1) {
            command += " ";
        }
    }

    if (!command.length() || (command.substr(0, 3) != "tar")) {
        return 1;
    }

    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    unsigned long returnValue;

    if (!CreateProcess(NULL, const_cast<char*>(command.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    GetExitCodeProcess(pi.hProcess, &returnValue);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);


    return (int)returnValue;

}


