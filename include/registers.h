#pragma once
#include <sys/types.h>
void regs_print(pid_t pid);
void regs_set(pid_t pid, const char *reg_name, unsigned long val);
