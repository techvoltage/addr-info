//system() and exit()
#define LIB "libc.so.6"
#include "addr-info.h"
int
main (void)
{
  void (*ptr) (void *);
  ptr = find_func_address ("system", LIB);
  char *bin_sh = "/bin/sh";
asm (".intel_syntax noprefix;" "push %[bin_sh];" "call %[ptr];" ".att_syntax noprefix;":
: [ptr] "r" (ptr), [bin_sh] "r" (bin_sh):);

  ptr = find_func_address ("exit", LIB);
asm (".intel_syntax noprefix;" "mov eax, %0;" "push 0;" "call eax;" ".att_syntax noprefix;":
: "r" (ptr):"eax");

  //ptr (0);
  printf ("Do not print me\n");
  return 0;

}
