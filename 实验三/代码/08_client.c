#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGKEY 0x24122233
struct message {
    long type;
    pid_t pid;
    pid_t ppid;
};

int main()
{
    int queue = msgget(MSGKEY, 0600);
    if (queue < 0) { perror("msgget"); return 1; }
    struct message msg = {0};
    msg.type = 1;
    msg.pid = getpid();
    if (msgsnd(queue, &msg, sizeof msg - sizeof(long), 0) < 0) {
        perror("msgsnd"); return 1;
    }
    /* 按本客户的 PID 接收回复。 */
    if (msgrcv(queue, &msg, sizeof msg - sizeof(long), getpid(), 0) < 0) {
        perror("msgrcv"); return 1;
    }
    printf("CLIENT pid=%ld received server_pid=%ld server_ppid=%ld\n",
           (long)getpid(), (long)msg.pid, (long)msg.ppid);
    return 0;
}
