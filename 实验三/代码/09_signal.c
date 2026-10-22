#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

volatile sig_atomic_t received = 0;

void handler(int signo)
{
    received = signo;
}

int main()
{
    int status;
    /* 在 fork 前注册，子进程会继承信号处理方式。 */
    if (signal(SIGUSR1, handler) == SIG_ERR) { perror("signal"); return 1; }
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return 1; }
    if (pid == 0) {
        printf("CHILD_READY pid=%ld waiting for SIGUSR1\n", (long)getpid());
        while (received == 0) sleep(1);
        printf("CHILD pid=%ld RECEIVED SIGUSR1 number=%d\n", (long)getpid(), (int)received);
        return 0;
    }
    if (kill(pid, SIGUSR1) < 0) { perror("kill"); return 1; }
    printf("PARENT pid=%ld SENT SIGUSR1 child=%ld\n", (long)getpid(), (long)pid);
    if (waitpid(pid, &status, 0) < 0) { perror("waitpid"); return 1; }
    if (WIFEXITED(status))
        printf("WAIT pid=%ld CHILD_EXIT=%d\n", (long)pid, WEXITSTATUS(status));
    return 0;
}
