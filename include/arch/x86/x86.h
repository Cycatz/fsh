#pragma once
#include <linux/version.h>

#define FSH_RET_INSTR_CODE 0xC3

#if (LINUX_VERSION_CODE <= KERNEL_VERSION(5, 7, 0))
#define FSH_HAS_KALLSYMS 1
#else
#define FSH_HAS_KALLSYMS 0
#endif


#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 11, 0))
#define FSH_HAS_FTRACE_REGS 1
#else
#define FSH_HAS_FTRACE_REGS 0
#endif


#if (LINUX_VERSION_CODE < KERNEL_VERSION(5, 11, 0))
#define FTRACE_OPS_FL_RECURSION 0
#endif
