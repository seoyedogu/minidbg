#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include "process.h"

static pid_t child_pid = 0;

pid_t proc_run(const char *path, char *const argv[]) {
    pid_t pid = fork();

    if (pid == 0) {
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        raise(SIGSTOP);
        execv(path, argv);
        perror("execv 실패");
        exit(1);

    } else {
        int status;
        child_pid = pid;

        // SIGSTOP 대기
        waitpid(pid, &status, 0);
        if (WIFSTOPPED(status)) {
            printf("[+] 프로세스 시작 (pid: %d)\n", pid);
            ptrace(PTRACE_CONT, pid, 0, 0);
        }

        while(1) {
            waitpid(pid, &status, 0);

            if (WIFEXITED(status)) {
                printf("[+] 프로그램 종료 (code : %d)\n", WEXITSTATUS(status));
                child_pid = 0;
                break;
            }
            if (WIFSTOPPED(status)) {
                int sig = WSTOPSIG(status);
                if (sig == SIGTRAP) {
                    printf("[+] 프로그램 실행 준비 완료\n");
                    ptrace(PTRACE_CONT, pid, 0,0);
                    usleep(100000); // 프롬프트 대기 시간
                    break;
                } else {
                    ptrace(PTRACE_CONT, pid, 0, 0);
                }
            }
        }
    }

    return child_pid;
}

void proc_quit(pid_t pid) {
    if (pid <= 0) {
        printf("[-] 실행 중인 프로세스가 없습니다\n");
        return;
    }
    int status;
    kill(pid, SIGSTOP);
    waitpid(pid, &status, 0);

    // DETACH 시도
    if (ptrace(PTRACE_DETACH, pid, 0, 0) == 0) {
        printf("[+] 프로세스 detach 완료 (pid: %d)\n", pid);
    } else {
        if (errno == ESRCH) {
            printf("[+] 프로세스가 이미 종료됐습니다\n");
        } else {
            perror("[-] detach 실패");
        }
    }
}