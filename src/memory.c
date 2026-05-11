#include "memory.h"
#include <stdio.h>
#include <errno.h>
#include <sys/ptrace.h>

void mem_dump(pid_t pid, unsigned long addr, int len) {
    for (int i = 0; i < len; i += 8) {
        errno = 0;
        long data = ptrace(PTRACE_PEEKDATA, pid, addr + i, NULL);
        if (errno != 0) {
            perror("[-] PEEKDATA 실패");
            return;
        }
        printf("0x%016lx: ", addr + i);
    
        unsigned char *bytes = (unsigned char *)&data;
        for (int j = 0; j < 8; j++) {
            printf("%02x ", bytes[j]);
        }
        printf("\n");
    }
}

void mem_write(pid_t pid, unsigned long addr, unsigned long val) {
    if (ptrace(PTRACE_POKEDATA, pid, addr, val) == -1) {
        perror("[-] POKEDATA 실패");
        return;
    }
    printf("[+] 0x%016lx 에 0x%016lx 작성 완료\n", addr, val);
}