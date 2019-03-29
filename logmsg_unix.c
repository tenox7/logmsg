// logmsg - output to stdout prefixed with current time

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

enum { INFO, WARNING, ERROR };

void logmsg(int s, char *msg, ...) {
    va_list ap;
    time_t t;
    struct tm *l;
    char *err[] = { "", " WARNING:", " ERROR:" };
    char hostname[255]={0};
    
    time(&t); 
    l=localtime(&t);
    gethostname(hostname, 255);
    if(s>2)
        s=2;
    printf("%04d/%02d/%02d %02d:%02d:%02d %s:%s ", 
        l->tm_year+1900, l->tm_mon+1, l->tm_mday, 
        l->tm_hour, l->tm_min, l->tm_sec, 
        hostname, err[s]
    );
    va_start(ap, msg);
    vprintf(msg, ap);
    va_end(ap);
    putchar('\n');
    if(s==2)
        exit(1);
}

int main() {

    logmsg(INFO, "hello %s %c", "world", '!');

    logmsg(WARNING, "oh %s %c", "no", '!');

    logmsg(ERROR, "oh %s %c", "shit", '!');

    logmsg(INFO, "hello %s %c", "world", '!'); 
    
    return 0;
}
