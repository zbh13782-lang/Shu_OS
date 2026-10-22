#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int global_value = 37;

int main()
{
    int local_value = 11, status;
    printf("BEFORE_FORK global=%d local=%d\n", global_value, local_value);
    pid_t child = fork();
    if (child < 0) { perror("fork"); return 1; }
    if (child == 0) {
        global_value += 9;
        local_value -= 3;
        printf("CHILD global=%d local=%d pid=%ld global_addr=%p local_addr=%p\n",
               global_value, local_value, (long)getpid(),
               (void *)&global_value, (void *)&local_value);
        /* Linux/GCC 下打印 main 的入口地址，观察程序代码的位置。 */
        printf("CODE_ADDR pid=%ld main=%p\n", (long)getpid(), (void *)main);
        return 0;
    }
    if (waitpid(child, &status, 0) < 0) { perror("waitpid"); return 1; }
    if (WIFEXITED(status))
        printf("WAIT pid=%ld CHILD_EXIT=%d\n", (long)child, WEXITSTATUS(status));
    printf("PARENT_AFTER_CHILD global=%d local=%d pid=%ld global_addr=%p local_addr=%p\n",
           global_value, local_value, (long)getpid(),
           (void *)&global_value, (void *)&local_value);
    printf("CODE_ADDR pid=%ld main=%p\n", (long)getpid(), (void *)main);
    global_value += 100;
    local_value += 1000;
    printf("PARENT_CHANGED global=%d local=%d\n", global_value, local_value);
    puts("Equal virtual addresses do not mean shared writable memory.");
    return 0;
}
