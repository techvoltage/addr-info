//system() and exit()
#include "addr-info.h"
int
main (void)
{
  void (*ptr) (void *);
  char *bin_sh = "/bin/sh";
  ptr = find_func_address ("system", "libc.so.6");
asm ("mov r0, %[bin_sh];" "blx %[ptr]":
: [ptr] "r" (ptr),[bin_sh] "r" (bin_sh):);

  ptr = find_func_address ("exit", "libc.so.6");
asm ("mov r0, 0;" "blx %[ptr];":
: [ptr] "r" (ptr):);

  //ptr (0);
  printf ("Do not print me\n");
  return 0;

}
