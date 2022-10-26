#include <linux/init.h>
#include "fsh.h"

static int __init fsh_init(void)
{
    unsigned i = 0;
    for (; i < fsh_num_hooks; i++) {
        int ret;
        struct fsh_hook *hook = (struct fsh_hook *) fsh_ops[i].private;
        pr_info("%s\n", hook->fname);
        ret = ftrace_set_filter(&fsh_ops[i], hook->fname, strlen(hook->fname), 0);
        if (ret < 0) {
            pr_alert("Setting ftrace filter failed with %d\n", ret);
            return ret;
        }
        register_ftrace_function(&fsh_ops[i]);
    }

    return 0;
}

static void __exit fsh_exit(void)
{
    unsigned i = 0;
    for (; i < fsh_num_hooks; i++) {
        unregister_ftrace_function(&fsh_ops[i]);
        ftrace_set_filter(&fsh_ops[i], NULL, 0, 1);
    }
}

module_init(fsh_init);
module_exit(fsh_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cycatz");
MODULE_DESCRIPTION(
    "A kernel module prints the program name being execved using ftrace");
