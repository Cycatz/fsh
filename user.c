#include "fsh.h"


SYSCALL_OVERRIDE(sys_execve)
{
    return 0;
}
