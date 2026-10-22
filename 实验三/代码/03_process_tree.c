#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    char mode[16];
    int generation = 0, status;
    pid_t pid;
    printf("Enter mode (tree/chain/siblings):\n");
    if (scanf("%15s", mode) != 1) return 1;
    if (strcmp(mode, "tree") && strcmp(mode, "chain") && strcmp(mode, "siblings"))
        return 2;
    printf("MODE=%s rounds=3\n", mode);
    printf("NODE pid=%ld ppid=%ld generation=0\n", (long)getpid(), (long)getppid());
    for (int i = 0; i < 3; i++) {
        pid = fork();
        if (pid < 0) { perror("fork"); return 1; }
        if (pid == 0) {
            generation++;
            printf("NODE pid=%ld ppid=%ld generation=%d\n",
                   (long)getpid(), (long)getppid(), generation);
            if (strcmp(mode, "siblings") == 0) break;
        } else {
            if (strcmp(mode, "chain") == 0) break;
        }
    }
    while ((pid = wait(&status)) > 0) {
        if (WIFEXITED(status))
            printf("WAIT pid=%ld CHILD_EXIT=%d\n", (long)pid, WEXITSTATUS(status));
    }
    return 0;
}
