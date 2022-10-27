#include <linux/ftrace.h>

/* Structure definitions */

typedef struct {
    const size_t *const args[6];
    const size_t *const origin;
    size_t *const retval;
} fsh_context_t;

typedef struct {
    char *fname;
    void *origin;
    bool (*hook)(fsh_context_t *);
} fsh_hook_t;



/* Function prototypes */
int fsh_init(void);
int fsh_exit(void);
void fsh_syscall_handler(unsigned long ip,
                         unsigned long parent_ip,
                         struct ftrace_ops *ops,
                         struct ftrace_regs *regs);


/* Variable prototypes */
extern struct ftrace_ops fsh_hook_ops[];
extern int fsh_num_hooks;


#define SYSCALL_OVERRIDE(sym) bool hook_##sym(fsh_context_t *context)
