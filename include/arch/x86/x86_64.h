#pragma once
#include "x86.h"

#define FSH_DECLARE_PREGS_FROM_CONTEXT(context)            \
    {                                                      \
        .di = *context->args[0], .si = *context->args[1],  \
        .dx = *context->args[2], .r10 = *context->args[3], \
        .r8 = *context->args[4], .r9 = *context->args[5],  \
    }

#define FSH_DECLARE_CONTEXT_FROM_PREGS(ftregs, fnregs, origin)      \
    {                                                               \
        .ftregs = (ftregs), .fnregs = (fnregs), .origin = (origin), \
        .args =                                                     \
            {                                                       \
                &fnregs->di,  &fnregs->si, &fnregs->dx,             \
                &fnregs->r10, &fnregs->r8, &fnregs->r9,             \
            },                                                      \
        .retval = &ftregs->ax,                                      \
    }



#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 17, 0))
#define FSH_SYSCALL_NAME(sym) ("__x64_" #sym)
#else
#define FSH_SYSCALL_NAME(sym) (#sym)
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 17, 0))
#define FSH_PTREGS_SYSCALL_STUBS 1
#else
#define FSH_PTREGS_SYSCALL_STUBS 0
#endif

/* Convert the first argument of ftregs to pt_regs */
#define FSH_GET_PTREGS_FROM_FTREGS(ftregs) (struct pt_regs *) ftregs->di;
