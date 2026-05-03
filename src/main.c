#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"
#include <sys/wait.h>

#define MAX_INPUT 256
#define MAX_ARGS  16

static void parse_input(char *input, char **cmd, char *args[], int *argc) {
    *cmd = strtok(input, " \n");
    *argc = 0;

    char *token;
    while ((token = strtok(NULL, " \n")) != NULL) {
        args[(*argc)++] = token;
        if (*argc >= MAX_ARGS - 1) break;
    }
    args[*argc] = NULL;
}

int main(void) {
    char input[MAX_INPUT];
    char *cmd;
    char *args[MAX_ARGS];
    int  argc;
    pid_t pid = 0;

    printf("minidbg 시작. 'help'로 명령어 확인\n");

    while (1) {
        printf("(minidbg) ");
        fflush(stdout);

        if (!fgets(input, sizeof(input), stdin)) break;
        if (input[0] == '\n') continue;

        parse_input(input, &cmd, args, &argc);
        if (!cmd) continue;

        if (strcmp(cmd, "run") == 0) {
            if (argc < 1) {
                printf("사용법: run <프로그램>\n");
                continue;
            }
            if (pid > 0) {
                printf("[-] 이미 실행 중인 프로세스가 있습니다.\n");
                continue;
            }
            pid = proc_run(args[0], args);
        } else if (strcmp(cmd, "quit") == 0 || strcmp(cmd, "q") == 0) {
            if (pid > 0) {
                int status;
                if (waitpid(pid, &status, WNOHANG) == pid) {
                    printf("[+] 프로세스 이미 종료됨\n");
                } else {
                    proc_quit(pid);
                }
            }
            printf("[+] 종료\n");
            break;

        } else if (strcmp(cmd, "help") == 0) {
            printf("명령어 목록:\n");
            printf("  run <prog>  프로그램 실행\n");
            printf("  quit        종료\n");

        } else {
            printf("[-] 알 수 없는 명령어: %s\n", cmd);
        }
    }

    return 0;
}