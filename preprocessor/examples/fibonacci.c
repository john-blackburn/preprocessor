#include "lib.h"
#include "lib.h"

#include "lib2.h"
#include "lib2.h"

#define THREE 3

#if 1+2==1+4-THREE+'\0'+'b'-'a'

  #if 1
    #define foo [(1+2-3)]
  #endif
  #define fib foo*foo
#endif

//#undef foo

#define min(x,y) ((x)<(y) ? (x) : (y))

int x = foo;

min(5*a, 2-b) + fib;

char c = '\n';

#ifndef fib
printf("I'm #ifdef foo='%d'\n",foo);  // #ifdef
#else
printf(bar,0xBAADF00D,0.123,123.4e-77, 3.14e+77, -3.14E10, 2+3+5) + 5.223f;
printf("at line: %d\n",__LINE__);
#endif

#if 0    // comment 2
/* stuff */
int y=1
#elif 1
int y=2
#elif 1
int y = 3
#else
/*ddfd
*/
int y=4
#endif

int fib(int n) {
    if (n == 0 || n == 1) {
        return n;
    } else {
        return fib(n - 1) + fib(n - 2);
    }
}

int main() {
    int n = 10;
    return fib(n);
}

/* { */
/*
blah
stuff
stuff
stuff
stuff*/

// path/to/foo/*.bat << this should not be the start of a comment.

#define nothing
nothing

#define VERSION 5
#if defined VERSION && VERSION>4
printf("version %d special features activated at %d\n", VERSION, __LINE__);
#endif

/* // not a single line comment */
