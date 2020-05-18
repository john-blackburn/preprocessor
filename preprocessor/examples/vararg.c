/*
  macro with one variable argument
*/

#define eprint(...) printf(__VA_ARGS__)

eprint("hello, world %d\n",2);

/*
  macro with one fixed argument and one variable argument
*/

#define qprint(format, ...) printf(format, __VA_ARGS__)

qprint("hello, world %d\n",2,3,4);
qprint("hello, world\n",);
