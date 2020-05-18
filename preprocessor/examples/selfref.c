#define x (4 + y)
#define y (2 * x)
#define foo (4 + foo)
#define EPERM EPERM

x
y
foo

#ifdef EPERM
printf("EPERM",EPERM,__LINE__);
#endif

#define NULL (void *)0

#ifdef STBI_NO_FAILURE_STRINGS
   #define e(x,y)  0
#elif defined(STBI_FAILURE_USERMSG)
   #define e(x,y)  e(y)
#else
   #define e(x,y)  e(x)
#endif

#define epf(x,y)   ((float *) (e(x,y)?NULL:NULL))
#define epuc(x,y)  ((unsigned char *) (e(x,y)?NULL:NULL))

if (output == NULL) { free(data); return epf("outofmem", "Out of memory"); }
