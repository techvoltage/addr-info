//system() and exit()
#define LIB "/system/lib/libc.so"
#include "addr-info.h"
int
main (void)
{
  void (*ptr) (void *);
  char *bin_sh = "/bin/sh";
  printf("DEBUG msg finding func address");
  ptr = find_func_address ("system", LIB);
  printf("DEBUG msg found func address");
  asm ("mov r0, %[bin_sh];" "blx %[ptr]":
: [ptr] "r" (ptr),[bin_sh] "r" (bin_sh):);

  ptr = find_func_address ("exit", LIB);
asm ("mov r0, #0;" "blx %[ptr];":
: [ptr] "r" (ptr):);

  //ptr (0);
  printf ("Do not print me\n");
  return 0;

}
