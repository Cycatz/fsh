#include "fsh.h"
#include <linux/kprobes.h>

size_t FSH_RET_ADDRESS;

#if FSH_HAS_KALLSYMS
static size_t fsh_lookup_syscall_addr(const char *name)
{
    return kallsyms_lookup_name(name);
}
#else
static size_t fsh_lookup_syscall_addr(const char *name)
{
    struct kprobe kp = {.symbol_name = name};
    size_t retval;

    if (register_kprobe(&kp) < 0) return 0;
    retval = (size_t) kp.addr;
    unregister_kprobe(&kp);
    return retval;
}
#endif

/**
 * __fsh_empty_func() - Provide a 'ret' instruction for handler to exit ftrace
 * This function is not callable.
 */
static noinline void __fsh_empty_func(void) {}

static void fsh_find_ret_instr(void)
{
    FSH_RET_ADDRESS = (size_t) __fsh_empty_func;
    while (*(unsigned char *) FSH_RET_ADDRESS != FSH_RET_INSTR_CODE) {
        ++FSH_RET_ADDRESS;
    }
}

int fsh_init(void)
{
    unsigned i = 0;

    fsh_find_ret_instr();
    for (; i < fsh_num_hooks; i++) {
        int ret;
        fsh_hook_t *hook = fsh_hook_ops[i].private;
        hook->origin = (void *) fsh_lookup_syscall_addr(hook->fname);
        ret = ftrace_set_filter_ip(&fsh_hook_ops[i],
                                   (unsigned long) hook->origin, 0, 0);
        if (ret < 0) {
            pr_alert("Setting ftrace filter failed with %d\n", ret);
            return ret;
        }
        register_ftrace_function(&fsh_hook_ops[i]);
    }

    return 0;
}

int fsh_exit(void)
{
    unsigned i = 0;
    for (; i < fsh_num_hooks; i++) {
        unregister_ftrace_function(&fsh_hook_ops[i]);
        ftrace_set_filter(&fsh_hook_ops[i], NULL, 0, 1);
    }
    return 0;
}
