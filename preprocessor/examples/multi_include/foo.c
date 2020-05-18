// Computed include
#define INCLUDE "lib/bar.h"
#include INCLUDE

/*
stuff
stuff
stuff
stuff
stuff
*/

printf("%d\n",__LINE__);
// more lines
printf("%s %d\n",__FILE__, __LINE__);
