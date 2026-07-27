#include "builtin_error.h"
#include <stdlib.h>

t_error	builtin_print_and_qualify(
			const char *builtin_name,
			t_error err,
			bool is_special_builtin,
			int *status)
{

	if (err.type == ERR_NO)
		return (err);
	*status = (int)err.type;
	err = error_print(err, builtin_name, NULL, NULL);
	if (err.type != ERR_INTERNAL && err.type != ERR_LIBC)
	{
		if (is_special_builtin == true)
			err.type = ERR_POSIX_BUILTIN_SPECIAL;
		else
			err.type = ERR_BUILTIN;
	}
	return (err);
}
