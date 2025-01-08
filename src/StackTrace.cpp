//---------------------------------------------------------------------------

#pragma hdrstop

#include "StackTrace.h"
#include <Windows.h>
#include <DbgHelp.h>
#include <memory>

#define MAX_FRAMES 64
//---------------------------------------------------------------------------
#pragma package(smart_init)

UnicodeString StackTrace::getStackTrace() {
    void* stack[MAX_FRAMES];
    UnicodeString trace = "";

    HANDLE process = GetCurrentProcess();
    SymInitialize(process, NULL, TRUE);
    SymSetOptions(SYMOPT_LOAD_LINES);

    WORD frames = CaptureStackBackTrace(0, MAX_FRAMES, stack, NULL);

    SYMBOL_INFO *symbol = (SYMBOL_INFO*) calloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char), 1);
    symbol->MaxNameLen = 255;
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

    DWORD displacement, error;
    IMAGEHLP_LINE64 *line = (IMAGEHLP_LINE64 *)malloc(sizeof(IMAGEHLP_LINE64));
    line->SizeOfStruct = sizeof(IMAGEHLP_LINE64);

	for (int i = 0; i < frames; i++) {

        SymFromAddr(process, (DWORD64)(stack[i]), 0, symbol);

        UnicodeString fname = "", lnNumber = "";

        if (SymGetLineFromAddr64(process, (DWORD64)(stack[i]), &displacement, line)) {
       		fname = line->FileName;
            lnNumber = IntToStr((int)line->LineNumber);
        }

        UnicodeString fcall = "[" + IntToStr(i) + "] " + symbol->Name + fname + lnNumber;

        trace += fcall;

    }
    free(line);
    free(symbol);

    return trace;
}

