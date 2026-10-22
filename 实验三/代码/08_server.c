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
    int queue = msgget(MSGKEY, IPC_CREAT | IPC_EXCL | 0600);
    if (queue < 0) { perror("msgget"); return 1; }
    printf("QUEUE_READY key=%d id=%d server_pid=%ld server_ppid=%ld clients=3\n",
           MSGKEY, queue, (long)getpid(), (long)getppid());
    struct message msg;
    for (int i = 0; i < 3; ++i) {
        /* 只接收类型 1 的请求，避免读到自己发出的回复。 */
        if (msgrcv(queue, &msg, sizeof msg - sizeof(long), 1, 0) < 0) {
            perror("msgrcv"); return 1;
        }
        printf("REQUEST client_pid=%ld\n", (long)msg.pid);
        msg.type = msg.pid;
        msg.pid = getpid();
        msg.ppid = getppid();
        if (msgsnd(queue, &msg, sizeof msg - sizeof(long), 0) < 0) {
            perror("msgsnd"); return 1;
        }
    }
    /* 最后一个客户读取回复后，由运行脚本删除队列。 */
    return 0;
}
