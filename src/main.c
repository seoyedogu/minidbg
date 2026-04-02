#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    if (argc <2) {
        printf("사용법 : %s <프로그램>\n", argv[0]);
        return 1;
    }
    pid_t pid = fork();
    
    if (pid == 0) {
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        raise(SIGSTOP);
        execv(argv[1], &argv[1]);
        perror("execv 실패");
        exit(1);
    } else {
        int status;
        while(1) {
            waitpid(pid, &status, 0);   

            if (WIFSTOPPED(status)) {
                int sig = WSTOPSIG(status);
                printf("[+] chil sstopped at signal %d\n", sig);
                ptrace(PTRACE_CONT, pid, 0, 0);
            } else if (WIFEXITED(status)) {
                printf("[+] child exited (code: %d)\n", WEXITSTATUS(status));
                break;
            } else if (WIFSIGNALED(status)) {
                printf("[!] child killed by signal %d\n", WTERMSIG(status));
                break;
            }
        }
    }
}