#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
//#include "apue.h"


void pr_exit(int status);

static int a;

int main(int argc, char* argv[]) {
    int N;
    if(argc != 2 || (N = atoi(argv[1])) < 1){
        fprintf(stderr, "Invalid Argument\n");
        exit(EXIT_FAILURE);
    }
    pid_t child_pid = 0;
    int count = 0, i;
    int child_status;
    
    for (i = 1; i <= N; i++) {
        if(child_pid != 0) {
            waitpid(child_pid, &child_status, 0);
            printf("Process: %d ", i);
            pr_exit(child_status);
            break;
        } else {
            printf("Process: %d ", i);
            printf("PID: %d  PPID: %d\n", (int)getpid(), (int)getppid());
            if(i < N)
                child_pid = fork();
        }
    }
    exit(EXIT_SUCCESS);
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
