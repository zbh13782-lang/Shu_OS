#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t p1, p2, p3, pid;
    int status;
    p1 = fork();
    if (p1 < 0) { perror("fork"); return 1; }
    if (p1 == 0) {
        execl("./hello", "hello", NULL);
        perror("hello");
        return 1;
    }
    p2 = fork();
    if (p2 < 0) { perror("fork"); return 1; }
    if (p2 == 0) {
        execlp("uname", "uname", "-sr", NULL);
        perror("uname");
        return 1;
    }
    p3 = fork();
    if (p3 < 0) { perror("fork"); return 1; }
    if (p3 == 0) {
        execlp("date", "date", "+%F %T %Z", NULL);
        perror("date");
        return 1;
    }
    while ((pid = wait(&status)) > 0) {
        if (WIFEXITED(status)) {
            if (pid == p1)
                printf("REAP pid=%ld program=hello exit=%d\n", (long)pid, WEXITSTATUS(status));
            else if (pid == p2)
                printf("REAP pid=%ld program=uname exit=%d\n", (long)pid, WEXITSTATUS(status));
            else if (pid == p3)
                printf("REAP pid=%ld program=date exit=%d\n", (long)pid, WEXITSTATUS(status));
        }
    }
    printf("ALL_CHILDREN_REAPED=3\n");
    return 0;
}
