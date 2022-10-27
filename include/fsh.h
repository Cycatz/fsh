#include <linux/ftrace.h>

/* Structure definitions */
typedef struct {
    char *fname;
    void *origin;
    void *hook;
} fsh_hook_t;

typedef struct {

} fsh_context_t;


// typedef struct _fsh_ops_elem_t {
//     ftrace_ops *ops;
//     fsh_ops_elem_t *next;
// } fsh_ops_elem_t;
// 
// typedef struct {
//     fsh_elem_t *head;
//     fsh_elem_t *tail; 
//     size_t size;
// } fsh_ops_list_t;

/* List operations */ 
// fsh_ops_list_t *fsh_ops_list_new(void);
// void            fsh_ops_list_free(fsh_ops_list_t *);
// int             fsh_ops_list_insert_tail(fsh_ops_list_t *, ftrace_ops *); 

/* Function prototypes */
int  fsh_init(void);
int  fsh_exit(void);
void fsh_syscall_handler(unsigned long ip,
                         unsigned long parent_ip,
                         struct ftrace_ops *ops,
                         struct ftrace_regs *regs);


/* Variable prototypes */
extern struct ftrace_ops fsh_hook_ops[];
extern int fsh_num_hooks;  


#define SYSCALL_OVERRIDE(sym) long hook_##sym(const fsh_context_t *context)
