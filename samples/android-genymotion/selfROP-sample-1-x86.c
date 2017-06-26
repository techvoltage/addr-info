//system() and exit()
#define LIB "/system/lib/libc.so"
#define DEBUG 1
#include "addr-info.h"
void (*ptr) (void *);
int
main (void)
{
  ptr = find_func_address ("system", LIB);
  char *bin_sh = "/system/bin/sh";
asm ("pushl %[bin_sh];" "call ptr;":
//asm ("pushl %%edx;" "call %%eax;":
: [ptr] "r" (ptr), [bin_sh] "r" (bin_sh):);

  ptr = find_func_address ("exit", LIB);
asm ("mov $0,%%eax;" "pushl $0;" "call ptr;":
: "r" (ptr):"eax");

  //ptr (0);
  printf ("Do not print me\n");
  return 0;

}
