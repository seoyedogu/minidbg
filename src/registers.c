/* regs 명령 — PTRACE_GETREGS / PTRACE_SETREGS */
#include "registers.h"
#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <string.h>

void regs_print(pid_t pid) {
    struct user_regs_struct regs;

    if (ptrace(PTRACE_GETREGS, pid, 0, &regs) == -1) {
        perror("[-] PTRACE_GETREGS 실패");
        return;
    }
 // 0x %포맷 0빈자리 0으로 채움, 16 최소 16자리, 11 long long, x 16진수 출력
    printf("rip = 0x%016llx\n", regs.rip);
    printf("rsp = 0x%016llx\n", regs.rsp);
    printf("rbp = 0x%016llx\n", regs.rbp);
    printf("rax = 0x%016llx\n", regs.rax);
    printf("rbx = 0x%016llx\n", regs.rbx);
    printf("rcx = 0x%016llx\n", regs.rcx);
    printf("rdx = 0x%016llx\n", regs.rdx);
    printf("rsi = 0x%016llx\n", regs.rsi);
    printf("rdi = 0x%016llx\n", regs.rdi);
    printf("r8  = 0x%016llx\n", regs.r8);
    printf("r9  = 0x%016llx\n", regs.r9);
    printf("r10 = 0x%016llx\n", regs.r10);
    printf("r11 = 0x%016llx\n", regs.r11);
    printf("r12 = 0x%016llx\n", regs.r12);
    printf("r13 = 0x%016llx\n", regs.r13);
    printf("r14 = 0x%016llx\n", regs.r14);
    printf("r15 = 0x%016llx\n", regs.r15);
    printf("eflags = 0x%016llx\n", regs.eflags);
}

void regs_set(pid_t pid, const char *reg_name, unsigned long val) {
    struct user_regs_struct regs;

    if (ptrace(PTRACE_GETREGS, pid, 0, &regs) == -1) {
        perror("[-] PTRACE_GETREGS 실패");
        return;
    }

    if      (strcmp(reg_name, "rip") == 0) regs.rip = val;
    else if (strcmp(reg_name, "rsp") == 0) regs.rsp = val;
    else if (strcmp(reg_name, "rbp") == 0) regs.rbp = val;
    else if (strcmp(reg_name, "rax") == 0) regs.rax = val;
    else if (strcmp(reg_name, "rbx") == 0) regs.rbx = val;
    else if (strcmp(reg_name, "rcx") == 0) regs.rcx = val;
    else if (strcmp(reg_name, "rdx") == 0) regs.rdx = val;
    else if (strcmp(reg_name, "rsi") == 0) regs.rsi = val;
    else if (strcmp(reg_name, "rdi") == 0) regs.rdi = val;
    else {
        printf("[-] 알 수 없는 레지스터: %s\n", reg_name);
        return;
    }
    if (ptrace(PTRACE_SETREGS, pid, 0, &regs) == -1) {
        perror("[-] PTRACE_SETREGS 실패");
        return;
    }
    printf("[+] %s = 0x%016lx\n", reg_name, val);
}