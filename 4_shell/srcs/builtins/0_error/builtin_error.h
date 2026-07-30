#ifndef BUILTIN_ERRO_H
# define BUILTIN_ERRO_H

#include "error.h"

t_error	builtin_print_and_qualify(
			const char *builtin_name,
			t_error err,
			bool is_special_builtin,
			int *status);

#endif
