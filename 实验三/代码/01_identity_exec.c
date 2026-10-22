#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int status;
    char choice;
    printf("PID=%ld PPID=%ld PGID=%ld\n",
           (long)getpid(), (long)getppid(), (long)getpgrp());
    printf("UID=%ld EUID=%ld GID=%ld EGID=%ld\n",
           (long)getuid(), (long)geteuid(), (long)getgid(), (long)getegid());
    printf("Waiting 5 seconds before fork/exec...\n");
    sleep(5);
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return 1; }
    if (pid == 0) {
        printf("EXEC pid=%ld -> ./hello\n", (long)getpid());
        execl("./hello", "hello", NULL);
        perror("execl");
        return 1;
    }
    if (waitpid(pid, &status, 0) < 0) { perror("waitpid"); return 1; }
    if (WIFEXITED(status))
        printf("WAIT pid=%ld CHILD_EXIT=%d\n", (long)pid, WEXITSTATUS(status));
    do {
        printf("Exit now? [Y/N]: ");
        if (scanf(" %c", &choice) != 1) return 1;
        if (choice != 'Y' && choice != 'y')
            printf("Still running; enter Y when you want to finish.\n");
    } while (choice != 'Y' && choice != 'y');
    printf("DONE\n");
    return 0;
}
