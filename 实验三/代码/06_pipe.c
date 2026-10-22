#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    int delay[2] = {0, 500};
    if (argc > 1) delay[0] = atoi(argv[1]);
    if (argc > 2) delay[1] = atoi(argv[2]);
    char *when = argc > 3 ? argv[3] : "before";
    if (delay[0] < 0 || delay[1] < 0) return 2;
    if (strcmp(when, "before") && strcmp(when, "after")) return 2;
    int fd[2], status;
    pid_t children[2];
    if (pipe(fd) < 0) { perror("pipe"); return 1; }
    printf("PARENT pid=%ld delay1=%d delay2=%d sleep=%s-write\n",
           (long)getpid(), delay[0], delay[1], when);
    for (int i = 0; i < 2; ++i) {
        children[i] = fork();
        if (children[i] < 0) { perror("fork"); return 1; }
        if (children[i] == 0) {
            close(fd[0]);
            if (!strcmp(when, "before")) usleep(delay[i] * 1000);
            char message[128];
            snprintf(message, sizeof message,
                     "RECEIVED child=%d pid=%ld ppid=%ld text=hello-parent\n",
                     i + 1, (long)getpid(), (long)getppid());
            /* 消息很短，一次 write 写入，避免两个子进程的内容交叉。 */
            if (write(fd[1], message, strlen(message)) < 0) {
                perror("write"); return 1;
            }
            close(fd[1]);
            if (!strcmp(when, "after")) usleep(delay[i] * 1000);
            printf("CHILD_DONE child=%d pid=%ld\n", i + 1, (long)getpid());
            return 0;
        }
    }
    close(fd[1]);
    /* read 可能合并多次 write；逐字节读取，以换行分隔两条消息。 */
    char ch, line[128];
    int used = 0, messages = 0;
    ssize_t n;
    while ((n = read(fd[0], &ch, 1)) > 0) {
        line[used++] = ch;
        if (ch == '\n') {
            line[used] = '\0';
            printf("PARENT pid=%ld %s", (long)getpid(), line);
            used = 0;
            ++messages;
        }
    }
    close(fd[0]);
    if (n < 0) { perror("read"); return 1; }
    for (int i = 0; i < 2; ++i) {
        if (waitpid(children[i], &status, 0) < 0) { perror("waitpid"); return 1; }
        if (WIFEXITED(status))
            printf("WAIT pid=%ld CHILD_EXIT=%d\n", (long)children[i], WEXITSTATUS(status));
    }
    printf("MESSAGES_RECEIVED=%d\n", messages);
    return 0;
}
