#include <linux/init.h>
#include <linux/module.h>
#include "fsh.h"


SYSCALL_OVERRIDE(sys_execve)
{
    char filename[256] = {0};

    if (strncpy_from_user(filename, (const char *) *(context->args[0]),
                          sizeof(filename) - 1) >= 0) {
        pr_info("fsh: %s is executed!\n", filename);
    }
    return true;
}


static int __init my_module_init(void)
{
    fsh_init();
    return 0;
}

static void __exit my_module_exit(void)
{
    fsh_exit();
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cycatz");
MODULE_DESCRIPTION(
    "A kernel module prints the program name being execved using ftrace");
