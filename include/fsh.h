#pragma once
#include <linux/ftrace.h>

#if defined(CONFIG_X86_64)
#include "arch/x86/x86_64.h"
#elif defined(CONFIG_X86_32)
#include "arch/x86/x86_32.h"
#else
#error Unsupported architecture!
#endif


#if !FSH_HAS_FTRACE_REGS
#define ftrace_regs pt_regs
#endif


#include "context.h"

/* Structure definitions */

typedef struct {
    struct pt_regs *const ftregs; /* Registers passed to the ftrace function */
    struct pt_regs *const fnregs; /* Registers passed to the hook function */
    const size_t *const args[6];  /* Arguments passed to the origin syscall */
    const size_t *const origin;   /* Saved origin system call */
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
size_t fsh_call_orig_syscall(fsh_context_t *context);
void fsh_ret_instruction(void);


/* Variable prototypes */
extern struct ftrace_ops fsh_hook_ops[];
extern int fsh_num_hooks;
extern size_t FSH_RET_ADDRESS;

/* User marcos */
#define FSH_SYSCALL_OVERRIDE(sym) \
    bool hook_##sym(fsh_context_t *FSH_FUNC_CONTEXT)
#define FSH_CALL_ORIG_SYSCALL() fsh_call_orig_syscall(FSH_FUNC_CONTEXT)
