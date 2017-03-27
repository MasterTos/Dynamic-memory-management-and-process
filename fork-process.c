#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
//#include "apue.h"

#define PRINT printf("PID: %d  PPID: %d\n", (int)getpid(), (int)getppid());

void pr_exit(int status);

static int a;

int main(int argc, char* argv[]) {
    int N = atoi(argv[1]);
    pid_t child_pid;
    int count = 0;
LOOP_FORK :
    if(child_pid != 0) {
        if(count == 5) return 0;
        count++;
        printf("parent L ");
        PRINT;
        wait(NULL);
    } else {
        printf("child : ");
        PRINT;
        child_pid = fork();
        goto LOOP_FORK;
    }

    return 0;
}

void pr_exit(int status) {
    if (WIFEXITED(status))
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status),
#ifdef WCOREDUMP
               WCOREDUMP(status) ? " (core file generated)" : "");
#else
               "");
#endif
    else if (WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}
