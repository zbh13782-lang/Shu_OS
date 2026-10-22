#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("HELLO pid=%ld ppid=%ld: a new program is running.\n",
           (long)getpid(), (long)getppid());
    return 0;
}
