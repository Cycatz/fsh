#include <linux/ftrace.h>
#include <linux/printk.h>
#include <fsh.h>


void fsh_syscall_handler(unsigned long ip,
                         unsigned long parent_ip,
                         struct ftrace_ops *ops,
                         struct ftrace_regs *regs)
{
    fsh_hook_t *hook = ops->private;
    pr_info("%s\n", hook->fname);
}
