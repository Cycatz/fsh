#include "fsh.h"

#define __SYSCALL(sym) \
    extern long hook_##sym(const fsh_context_t *context);
#include <gen/overrided_syscalls.h>
#undef __SYSCALL



#define __SYSCALL(sym)                                              \
    {                                                               \
        .func = &fsh_syscall_handler,                               \
        .flags = FTRACE_OPS_FL_SAVE_REGS | FTRACE_OPS_FL_RECURSION, \
        .private =                                                  \
            &(fsh_hook_t){                                     \
                .fname = "__x64_" #sym,                             \
                .hook = &hook_##sym,                                \
            },                                                      \
    },

struct ftrace_ops fsh_hook_ops[] = {
#include <gen/overrided_syscalls.h>
};
#undef __SYSCALL

int fsh_num_hooks = sizeof(fsh_hook_ops) / sizeof(struct ftrace_ops);
