#define min(X, Y)  ((X) < (Y) ? (X) : (Y))

x = min(a, b);          //  x = ((a) < (b) ? (a) : (b));
y = min(1, 2);          //  y = ((1) < (2) ? (1) : (2));
z = min(a + 28, *p);    //  z = ((a + 28) < (*p) ? (a + 28) : (*p));


min (min (a, b), c)

min(, b)        // ((   ) < (b) ? (   ) : (b))
min(a, )        // ((a  ) < ( ) ? (a  ) : ( ))
min(,)          // ((   ) < ( ) ? (   ) : ( ))
min((,),)       // (((,)) < ( ) ? ((,)) : ( ))

//min()           // warning C4003: not enough arguments for function-like macro invocation 'min'
//min(,,)         // warning C4002: too many arguments for function-like macro invocation 'min'
