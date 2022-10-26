#include <linux/ftrace.h>


/* Structure definitions */
struct fsh_hook {
    char *fname;
    void *origin;
    void *hook;
};

struct fsh_context {
};

/* Function prototypes */
void fsh_syscall_handler(unsigned long ip,
                         unsigned long parent_ip,
                         struct ftrace_ops *ops,
                         struct ftrace_regs *regs);


/* Variable prototypes */
extern struct ftrace_ops fsh_ops[];
extern int fsh_num_hooks;


#define SYSCALL_OVERRIDE(sym) long hook_##sym(const struct fsh_context *context)
