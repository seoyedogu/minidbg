#pragma once
#include <sys/types.h>
int  proc_run(const char *path, char *const argv[]);
void proc_quit(pid_t pid);
