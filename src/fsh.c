#include "fsh.h"

int fsh_init(void)
{
    unsigned i = 0;
    for (; i < fsh_num_hooks; i++) {
        int ret;
        fsh_hook_t *hook = fsh_hook_ops[i].private;
        pr_info("%s\n", hook->fname);
        ret = ftrace_set_filter(&fsh_hook_ops[i], hook->fname,
                                strlen(hook->fname), 0);
        if (ret < 0) {
            pr_alert("Setting ftrace filter failed with %d\n", ret);
            return ret;
        }
        register_ftrace_function(&fsh_hook_ops[i]);
    }

    return 0;
}

int fsh_exit(void)
{
    unsigned i = 0;
    for (; i < fsh_num_hooks; i++) {
        unregister_ftrace_function(&fsh_hook_ops[i]);
        ftrace_set_filter(&fsh_hook_ops[i], NULL, 0, 1);
    }
    return 0;
}
