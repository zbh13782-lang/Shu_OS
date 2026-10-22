#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define CAPACITY 3
#define EMPTY 0
#define FULL 1
#define MUTEX 2

struct buffer {
    int data[CAPACITY];
    int in, out, count, produced, consumed, sum;
};
union semun { int val; };

int main()
{
    int items = 12;
    int shmid = shmget(IPC_PRIVATE, sizeof(struct buffer), IPC_CREAT | 0600);
    if (shmid < 0) { perror("shmget"); return 1; }
    struct buffer *b = shmat(shmid, NULL, 0);
    if (b == (void *)-1) {
        perror("shmat"); shmctl(shmid, IPC_RMID, NULL); return 1;
    }
    memset(b, 0, sizeof *b);
    int semid = semget(IPC_PRIVATE, 3, IPC_CREAT | 0600);
    if (semid < 0) {
        perror("semget"); shmdt(b); shmctl(shmid, IPC_RMID, NULL); return 1;
    }
    union semun arg;
    arg.val = CAPACITY;
    if (semctl(semid, EMPTY, SETVAL, arg) < 0) { perror("semctl"); return 1; }
    arg.val = 0;
    if (semctl(semid, FULL, SETVAL, arg) < 0) { perror("semctl"); return 1; }
    arg.val = 1;
    if (semctl(semid, MUTEX, SETVAL, arg) < 0) { perror("semctl"); return 1; }
    /* 每组操作先申请资源，再申请互斥锁；完成后先解锁，再释放资源。 */
    struct sembuf produce_begin[2] = {{EMPTY, -1, 0}, {MUTEX, -1, 0}};
    struct sembuf produce_end[2] = {{MUTEX, 1, 0}, {FULL, 1, 0}};
    struct sembuf consume_begin[2] = {{FULL, -1, 0}, {MUTEX, -1, 0}};
    struct sembuf consume_end[2] = {{MUTEX, 1, 0}, {EMPTY, 1, 0}};
    printf("BUFFER capacity=%d items=%d producer_pid=%ld\n", CAPACITY, items, (long)getpid());
    pid_t child = fork();
    if (child < 0) {
        perror("fork"); semctl(semid, 0, IPC_RMID);
        shmdt(b); shmctl(shmid, IPC_RMID, NULL); return 1;
    }
    if (child == 0) {
        for (int i = 0; i < items; ++i) {
            if (semop(semid, consume_begin, 2) < 0) { perror("semop"); return 1; }
            int value = b->data[b->out];
            b->out = (b->out + 1) % CAPACITY;
            --b->count;
            ++b->consumed;
            b->sum += value;
            printf("CONSUME value=%d count=%d pid=%ld\n", value, b->count, (long)getpid());
            if (semop(semid, consume_end, 2) < 0) { perror("semop"); return 1; }
            usleep(120000);
        }
        shmdt(b);
        return 0;
    }
    for (int value = 1; value <= items; ++value) {
        if (semop(semid, produce_begin, 2) < 0) { perror("semop"); return 1; }
        b->data[b->in] = value;
        b->in = (b->in + 1) % CAPACITY;
        ++b->count;
        ++b->produced;
        printf("PRODUCE value=%d count=%d pid=%ld\n", value, b->count, (long)getpid());
        if (semop(semid, produce_end, 2) < 0) { perror("semop"); return 1; }
        usleep(25000);
    }
    int status;
    if (waitpid(child, &status, 0) < 0) { perror("waitpid"); return 1; }
    if (WIFEXITED(status))
        printf("WAIT pid=%ld CHILD_EXIT=%d\n", (long)child, WEXITSTATUS(status));
    printf("SUMMARY produced=%d consumed=%d sum=%d count=%d\n",
           b->produced, b->consumed, b->sum, b->count);
    printf("SEMAPHORES empty=%d full=%d mutex=%d\n",
           semctl(semid, EMPTY, GETVAL), semctl(semid, FULL, GETVAL),
           semctl(semid, MUTEX, GETVAL));
    shmdt(b);
    if (shmctl(shmid, IPC_RMID, NULL) < 0) { perror("shmctl"); return 1; }
    if (semctl(semid, 0, IPC_RMID) < 0) { perror("semctl"); return 1; }
    puts("IPC_CLEANED");
    return 0;
}
