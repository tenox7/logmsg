//
// easy error routine resolving windows error codes to a string
// allows programm termination when first argument is 1
// ANSI flavor
//

#include <windows.h>
#include <stdio.h>

void error(int exit, char *msg, ...) {
    va_list valist;
    char vaBuff[1024]={'\0'};
    char errBuff[1024]={'\0'};
    DWORD err;

    err=GetLastError();
    va_start(valist, msg);_vsnprintf_s(vaBuff, sizeof(vaBuff), sizeof(vaBuff), msg, valist);va_end(valist);
    printf("%s: %s\n", (exit) ? "ERROR":"WARNING", vaBuff);
    if (err) {
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), errBuff, sizeof(errBuff), NULL);
        printf("[0x%08X] %s\n\n", err, errBuff);
    }
    else {
        putchar('\n');
    }
    FlushFileBuffers(GetStdHandle(STD_OUTPUT_HANDLE));
    if(exit)
        ExitProcess(1);
}


//
// example usage...
//
int main(int argc, char **argv) {

    error(0, "example, %s will continue... %d", argv[0], 123);

    error(1, "example, %s will terminate... %d", argv[0], 456);

    return 0;
}