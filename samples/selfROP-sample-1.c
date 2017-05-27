//system() and exit()
#include "addr-info.h"
int
main (void)
{
  void (*ptr) (void *);
  ptr = find_func_address ("system", "libc.so.6");
  char *bin_sh = "/bin/sh";
asm (".intel_syntax noprefix;" "mov eax, %0;" "mov ebx, %1;" "push ebx;" "call eax;" ".att_syntax noprefix;":
: "r" (ptr), "r" (bin_sh):"eax", "ebx");

  ptr = find_func_address ("exit", "libc.so.6");
asm (".intel_syntax noprefix;" "mov eax, %0;" "push 0;" "call eax;" ".att_syntax noprefix;":
: "r" (ptr):"eax");

  ptr (0);
  printf ("Do not print me\n");
  return 0;

}
