#include <linux/ftrace.h>

#include "fsh.h"


#define __SYSCALL(sym) \
    extern asmlinkage long origin_##sym(const struct pt_regs *);
#include <gen/overrided_syscalls.h>
#undef __SYSCALL


#define __SYSCALL(sym) \
    extern asmlinkage long hook_##sym(const struct fsh_context *context);
#include <gen/overrided_syscalls.h>
#undef __SYSCALL



#define __SYSCALL(sym)                                              \
    {                                                               \
        .func = &fsh_syscall_handler,                               \
        .flags = FTRACE_OPS_FL_SAVE_REGS | FTRACE_OPS_FL_RECURSION, \
        .private =                                                  \
            &(struct fsh_hook){                                     \
                .fname = "__x64_" #sym,                             \
                .origin = &origin_##sym,                            \
                .hook = &hook_##sym,                                \
            },                                                      \
    },

struct ftrace_ops fsh_ops[] = {
#include <gen/overrided_syscalls.h>
};
#undef __SYSCALL

int fsh_num_hooks = sizeof(fsh_ops) / sizeof(struct ftrace_ops);
