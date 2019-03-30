#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/utsname.h>

enum { INFO, WARNING, ERROR };

void logmsg(int s, char *msg, ...) {
    va_list ap;
    time_t t;
    struct tm *l;
    struct utsname u;
    char *err[] = { "", " WARNING:", " ERROR:" };
    
    time(&t); 
    l=localtime(&t);
    uname(&u);
    if(s>2) s=2;
    if(s<0) s=0;
    fflush(stdout);
    printf("%04d/%02d/%02d %02d:%02d:%02d %s:%s ", 
        l->tm_year+1900, l->tm_mon+1, l->tm_mday, 
        l->tm_hour, l->tm_min, l->tm_sec, 
        u.nodename, err[s]
    );
    va_start(ap, msg);
    vprintf(msg, ap);
    va_end(ap);
    if(s)
        printf(" [%s (%d)]", strerror(errno), errno);
    putchar('\n');
    fflush(stdout);
    if(s==ERROR)
        exit(1);
}

int main() {

    logmsg(INFO, "hello %s %c", "world", '!');

    logmsg(WARNING, "oh %s %c", "no", '!');

    fopen("/dev/null", "invalid");    

    logmsg(ERROR, "oh %s %c", "shit", '!');

    logmsg(INFO, "this did not happen"); 
    
    return 0;
}
