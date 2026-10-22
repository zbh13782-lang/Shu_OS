#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    char mode[16];
    int fd[2], status;
    pid_t parent = getpid(), pid;
    printf("Enter mode (reap/orphan):\n");
    if (scanf("%15s", mode) != 1) return 1;
    if (strcmp(mode, "orphan") == 0) {
        pid = fork();
        if (pid < 0) { perror("fork"); return 1; }
        if (pid == 0) {
            sleep(2);
            printf("ORPHAN pid=%ld old_ppid=%ld new_ppid=%ld\n",
                   (long)getpid(), (long)parent, (long)getppid());
        } else {
            printf("PARENT_EXIT pid=%ld child=%ld (without wait)\n",
                   (long)parent, (long)pid);
        }
        return 0;
    }
    if (strcmp(mode, "reap") != 0) return 2;
    if (pipe(fd) < 0) { perror("pipe"); return 1; }
    pid = fork();
    if (pid < 0) { perror("fork"); return 1; }
    if (pid == 0) {
        char message[] = "work-finished";
        close(fd[0]);
        if (write(fd[1], message, sizeof message) < 0) { perror("write"); return 1; }
        close(fd[1]);
        return 42;
    }
    close(fd[1]);
    char message[80] = {0};
    if (read(fd[0], message, sizeof message - 1) < 0) { perror("read"); return 1; }
    close(fd[0]);
    printf("PIPE_MESSAGE child=%ld text=%s\n", (long)pid, message);
    if (waitpid(pid, &status, 0) < 0) { perror("waitpid"); return 1; }
    if (WIFEXITED(status))
        printf("WAIT pid=%ld CHILD_EXIT=%d\n", (long)pid, WEXITSTATUS(status));
    return 0;
}
