#pragma once

#include "logger.h"

#ifdef PCONFIG_DEBUG

#define PASSERT(expr)                                                                    \
    {                                                                                    \
        if (expr)                                                                        \
        {                                                                                \
        }                                                                                \
        else                                                                             \
        {                                                                                \
            PERROR("Assertion {0} failed in {1} at line {2}", PSTR(expr), PFILE, PLINE); \
            PBREAK;                                                                      \
        }                                                                                \
    }

#define PASSERT_MSG(expr, message)                                                                      \
    {                                                                                                   \
        if (expr)                                                                                       \
        {                                                                                               \
        }                                                                                               \
        else                                                                                            \
        {                                                                                               \
            PERROR("Assertion {0} failed in {1} at line {2} \n{3}", PSTR(expr), PFILE, PLINE, message); \
            PBREAK;                                                                                     \
        }                                                                                               \
    }
#else
#define PASSERT(expr)                  void()
#define PASSERT_MSG(expr, message)     void()
#endif // PCONFIG_DEBUG