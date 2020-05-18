#define xstr(s) str(s)
#define str(s) #s
#define foo 4
str (foo)    // "foo"
xstr (foo)   // xstr (4) = str (4) = "4"
