//
// easy error routine resolving windows error codes to a string
// allows programm termination when first argument is 1
// UNICODE flavor
//

#include <windows.h>
#include <stdio.h>

void error(int exit, WCHAR *msg, ...) {
    va_list valist;
    WCHAR vaBuff[1024]={L'\0'};
    WCHAR errBuff[1024]={L'\0'};
    DWORD err;

    err=GetLastError();
    va_start(valist, msg);_vsnwprintf_s(vaBuff, sizeof(vaBuff), sizeof(vaBuff), msg, valist);va_end(valist);
    wprintf(L"%s: %s\n", (exit) ? L"ERROR":L"WARNING", vaBuff);
    if (err) {
        FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), errBuff, sizeof(errBuff), NULL);
        wprintf(L"[0x%08X] %s\n\n", err, errBuff);
    }
    else {
        putchar(L'\n');
    }
    FlushFileBuffers(GetStdHandle(STD_OUTPUT_HANDLE));
    if(exit)
        ExitProcess(1);
}


//
// example usage...
//
int wmain(int argc, WCHAR **argv) {

    error(0, L"example, %s will continue... %d", argv[0], 123);

    error(1, L"example, %s will terminate... %d", argv[0], 456);

    return 0;
}