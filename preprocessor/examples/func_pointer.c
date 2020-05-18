extern void foo(void);
#define foo() bar(NULL,1,2,3)

  foo();          // bar(NULL,1,2,3)
  funcptr = foo;  // no expansion

#define add(a,b) a+b

add+add(1,add(2,2))
+add(1,3)
+add
foo

add(add(1,add(2,2))+add(1,3),add)
