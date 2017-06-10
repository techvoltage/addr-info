//system() and exit()
#include "addr-info.h"
#define PATTERN "/bin/sh"
#define FUNC "system"
#define LIB "libc.so.6"
//#define LIB "/lib/i386-linux-gnu/libc.so.6"
#define LIBBASE "ld.so"

int
main (void)
{
  struct p_struct *p = malloc (sizeof *p);
  strncpy (p->pattern, PATTERN, sizeof p->pattern);
  p->patternlen = strlen (p->pattern);
  p->pattern_addr = NULL;
  void *ptr = find_func_address (FUNC, LIB);
  void *lib_base = find_lib_base (LIB);
  find_pattern_init (p);
  printf ("%s loaded at %p\n", LIBBASE, lib_base);
  printf ("%s in %s found at %p \n", FUNC, LIB, ptr);
  return 0;
}
