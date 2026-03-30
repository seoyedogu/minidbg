#pragma once
#include <sys/types.h>
void mem_dump(pid_t pid, unsigned long addr, int len);
void mem_write(pid_t pid, unsigned long addr, unsigned long val);
