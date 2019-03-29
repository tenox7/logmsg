// logmsg - output to stdout prefixed with current time

#include <stdio.h>
#include <time.h>
#include <stdarg.h>

void logmsg(char *msg, ...) {
    va_list ap;
    time_t t;
    struct tm *l;
    
    time(&t);
    l=localtime(&t);
    
    printf("%04d/%02d/%02d %02d:%02d:%02d: ", 
        l->tm_year+1900, 
        l->tm_mon+1, 
        l->tm_mday, 
        l->tm_hour, 
        l->tm_min, 
        l->tm_sec
    );
    va_start(ap, msg);
    vprintf(msg, ap);
    va_end(ap);
    putchar('\n');
}

int main() {

    logmsg("hello %s %c", "world", '!');
    
    return 0;
}
