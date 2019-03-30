#include <windows.h>
#include <stdio.h>

enum { LINFO, LWARNING, LERROR };

void logmsg(int s, LPWSTR msg, ...) {
    va_list ap;
    LPWSTR errBuff=NULL;
    LPWSTR n=NULL;
    DWORD e;
    SYSTEMTIME l;
    LPWSTR err[] = { L"", L" WARNING:", L" ERROR:" };

    GetLocalTime(&l);
    wprintf(L"%04d/%02d/%02d %02d:%02d:%02d %s:%s ", 
        l.wYear, l.wMonth, l.wDay, 
        l.wHour, l.wMinute, l.wSecond,
        _wgetenv(L"COMPUTERNAME"), err[s]
    );

    va_start(ap, msg);
    vwprintf(msg, ap);
    va_end(ap);

    if(s>2) s=2;
    if(s<0) s=0;

    if(s) {
        e=GetLastError();
        if(e) {
            FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER, 
                NULL, e, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR) &errBuff, 64, NULL);
            n=wcschr(errBuff, L'\r');
            if(n)
                *n=L'\0';
            wprintf(L" [%s (0x%08X)]", errBuff, e);
        }
    }
    putchar(L'\n');
    if(s==LERROR)
        ExitProcess(1);
}



int wmain(int argc, WCHAR **argv) {

    logmsg(LINFO, L"hello %s %c", L"world", L'!');

    logmsg(LWARNING, L"oh %s %c", L"no", L'!');

    FlushFileBuffers(GetStdHandle(STD_OUTPUT_HANDLE));

    logmsg(LERROR, L"oh %s %c", L"shit", L'!');

    logmsg(LINFO, L"this did not happen"); 

    return 0;
}
