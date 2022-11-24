#pragma once
#include "x86.h"

#define FSH_PTREGS_SYSCALL_STUBS 0
#define FSH_SYSCALL_NAME(sym) (#sym)

#define FSH_DECLARE_PREGS_FROM_CONTEXT(context)           \
    {                                                     \
        .bx = *context->args[0], .cx = *context->args[1], \
        .dx = *context->args[2], .si = *context->args[3], \
        .di = *context->args[4], .bp = *context->args[5], \
    }

#define FSH_DECLARE_CONTEXT_FROM_PREGS(ftregs, fnregs, origin)      \
    {                                                               \
        .ftregs = (ftregs), .fnregs = (fnregs), .origin = (origin), \
        .args =                                                     \
            {                                                       \
                &fnregs->bx, &fnregs->cx, &fnregs->dx,              \
                &fnregs->si, &fnregs->di, &fnregs->bp,              \
            },                                                      \
        .retval = &ftregs->ax,                                      \
    }

/* In fact, we don't need this in x86-32 since FSH_PTREGS_SYSCALL_STUBS is
 * false */
/* Convert the first argument of ftregs to pt_regs */
#define FSH_GET_PTREGS_FROM_FTREGS(ftregs) (struct pt_regs *) ftregs->bx;
