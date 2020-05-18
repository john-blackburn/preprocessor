#define macro(a,b) a & b
#define macro1(a) A[a]

macro (array[x = y, x + 1]) // array[x = y & x + 1]
macro1 (array[(x = y, x + 1)])  // A[array[(x = y, x + 1)]]
