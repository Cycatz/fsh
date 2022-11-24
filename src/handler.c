#include <linux/ftrace.h>
#include <linux/printk.h>

#include <fsh.h>

#if !FSH_HAS_FTRACE_REGS
static __always_inline struct pt_regs *ftrace_get_regs(
    struct ftrace_regs *fregs)
{
    return fregs;
}
#endif

size_t fsh_call_orig_syscall(fsh_context_t *context)
{
#if FSH_PTREGS_SYSCALL_STUBS
    return ((asmlinkage size_t(*)(struct pt_regs *)) context->origin)(
        context->fnregs);
#elif
    return ((asmlinkage size_t(*)(size_t, size_t, size_t, size_t, size_t,
                                  size_t)) context->origin)(
        *context->args[0], *context->args[1], *context->args[2],
        *context->args[3], *context->args[4], *context->args[5]);
#endif
}

void fsh_syscall_handler(unsigned long ip,
                         unsigned long parent_ip,
                         struct ftrace_ops *ops,
                         struct ftrace_regs *fregs)
{
    fsh_hook_t *hook = ops->private;
    struct pt_regs *ftregs = ftrace_get_regs(fregs);

#if FSH_PTREGS_SYSCALL_STUBS
    struct pt_regs *fnregs = FSH_GET_PTREGS_FROM_FTREGS(ftregs);
#elif
    struct pt_regs *fnregs = ftregs;
#endif

    void *origin = hook->origin;
    fsh_context_t context =
        FSH_DECLARE_CONTEXT_FROM_PREGS(ftregs, fnregs, origin);

    if (!within_module(parent_ip, THIS_MODULE)) {
        /* Call hook function */
        if (!hook->hook(&context)) {
            ftregs->ip = FSH_RET_ADDRESS;
        }
    }
}
