#pragma once
#include <sys/types.h>

typedef struct breakpoint {
    unsigned long     addr;
    unsigned char     orig_byte;
    int               enabled;
    int               id;
    struct breakpoint *next;
} Breakpoint;

void bp_set(pid_t pid, unsigned long addr);
void bp_delete(pid_t pid, int id);
void bp_list(void);
void bp_handle_hit(pid_t pid);
