#ifndef BUILTIN_USAGE_H
# define BUILTIN_USAGE_H

#include "error.h"

t_error	builtin_error_usage(const char *builtin, const char *usage);

t_error	builtin_error_flag(const char *builtin, const char *flag);

#endif
