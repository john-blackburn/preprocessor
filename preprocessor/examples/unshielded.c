#define foo (a,b)            // replace with #define foo (a,b) (object-like) to make this work
#define bar(x) lose(x)
#define lose(x) (1 + (x))   // (1+((a,b))) when it works

bar(foo)  // Error: lose requires a single argument
