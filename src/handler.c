#include <fsh.h>
#include <linux/ftrace.h>
#include <linux/printk.h>


void fsh_syscall_handler(unsigned long ip,
                         unsigned long parent_ip,
                         struct ftrace_ops *ops,
                         struct ftrace_regs *fregs)
{
    fsh_hook_t *hook = ops->private;
    struct pt_regs *pregs = ftrace_get_regs(fregs);
    struct pt_regs *regs = (struct pt_regs *) pregs->di;

    fsh_context_t context = {
        .args =
            {
                &regs->di,
                &regs->si,
                &regs->dx,
                &regs->r10,
                &regs->r8,
                &regs->r9,
            },
        .retval = &regs->ax,
    };

    hook->hook(&context);
}
