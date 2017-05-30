//system() and exit()
#include "addr-info.h"
int
main (void)
{
  void (*ptr) (void *);
  ptr = find_func_address ("system", "libc.so");
  char *bin_sh = "/bin/sh";
asm (".intel_syntax noprefix;" "mov rdi, %[bin_sh];" "call %[ptr];" ".att_syntax noprefix;":
: [ptr] "r" (ptr), [bin_sh] "r" (bin_sh):);

  ptr = find_func_address ("exit", "libc.so");
asm (".intel_syntax noprefix;" "mov rax, %0;" "mov rdi,0;" "call rax;" ".att_syntax noprefix;":
: "r" (ptr):"rax");

  //ptr (0);
  printf ("Do not print me\n");
  return 0;

}
