#pragma once


#define FSH_FUNC_ARG1 (FSH_FUNC_CONTEXT->args[0])
#define FSH_FUNC_ARG2 (FSH_FUNC_CONTEXT->args[1])
#define FSH_FUNC_ARG3 (FSH_FUNC_CONTEXT->args[2])
#define FSH_FUNC_ARG4 (FSH_FUNC_CONTEXT->args[3])
#define FSH_FUNC_ARG5 (FSH_FUNC_CONTEXT->args[4])
#define FSH_FUNC_ARG6 (FSH_FUNC_CONTEXT->args[5])

#define FSH_SET_RETVAL(x)              \
    do {                               \
        *FSH_FUNC_CONTEXT->retval = x; \
    } while (0)
