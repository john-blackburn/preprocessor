#define version 5

#if defined version && version>4 && (-1+2*3==version || version == 1) && foo==1
iftrue
#elif defined version && version>4 && (-1+2*3==version || version == 1) && foo==0
eliftrue
#endif
