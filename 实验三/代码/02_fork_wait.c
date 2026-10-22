#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t result = fork();
    if (result < 0) { perror("fork"); return 1; }
    if (result == 0) {
        printf("CHILD pid=%ld ppid=%ld fork_return=0\n", (long)getpid(), (long)getppid());
        return 23;
    }
    printf("PARENT pid=%ld fork_return=%ld\n", (long)getpid(), (long)result);
    int status;
    if (waitpid(result, &status, 0) < 0) { perror("waitpid"); return 1; }
    if (WIFEXITED(status))
        printf("WAIT pid=%ld CHILD_EXIT=%d\n", (long)result, WEXITSTATUS(status));
    puts("Parent has reclaimed the child's exit status.");
    return 0;
}
