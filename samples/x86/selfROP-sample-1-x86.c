//system() and exit()
#define LIB "/system/lib/libc.so"
#define DEBUG 1
#include "addr-info.h"
void (*ptr) ();
//extern "C" {
//  void foo() {
//	  // do something
//  }__attribute__((used))
//}

int main (void)
{
  ptr = find_func_address ("system", LIB);
  char *bin_sh = "/system/bin/sh";

//asm ("pushl %%edx;" "call %%eax;":
//: [ptr] "r" (ptr), [bin_sh] "r" (bin_sh):);
asm ("pushl %0;": //"call %%eax;":
: "g" (bin_sh): "eax");
ptr();
  ptr = find_func_address ("exit", LIB);
asm ("mov $0,%%eax;" "pushl $0;":// "call ptr;":
: "r" (ptr):"eax");
ptr();
  //ptr (0);
  printf ("Do not print me\n");
  return 0;

}
