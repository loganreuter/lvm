#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdarg.h>

#define TRUE (1);
#define FALSE (0);
typedef int boolean;

const boolean IS_DEBUGGING = TRUE;

inline int __cdecl test_passed(){
    printf("\033[0;32m PASSED\033[0m\n");
}

inline int __cdecl test_failed(const char *_Format, ...){
    va_list arg;
    int done;

    printf("\033[0;31m FAILED:\t");

    va_start(arg, _Format);
    done = vfprintf(stdout, _Format, arg);
    va_end(arg);

    printf("\033[0m\n");
    
    return done;
}

inline int __cdecl DEBUG(const char *_Format, ...){
    int done = 0;
    if(IS_DEBUGGING){
        va_list arg;

        printf("\033[0;35m DEBUG:\t");

        va_start(arg, _Format);
        done = vfprintf(stdout, _Format, arg);
        va_end(arg);

        printf("\033[0m\n");
    }

    return done;
}
#endif