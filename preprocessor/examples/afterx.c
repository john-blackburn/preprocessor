/*
This shows that normal arguments are fully expanded before inclusion
While ## arguments are not expanded
*/

# define AFTERX(x) X_ ## x
# define XAFTERX(x) AFTERX(x)
#  define TABLESIZE 1024
#  define BUFSIZE TABLESIZE

AFTERX(BUFSIZE) // X_BUFSIZE
XAFTERX(BUFSIZE) // X_1024
	virtual void Dump() { b2Log("// Dump is not supported for this joint type.\n"); } // comment
