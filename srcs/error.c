#include "error.h"
#include "posix_helpers.h"
#include "shell.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define SEPARATOR		": "

// TODO: split in 2 functions
const char	*error_to_string(t_error error)
{
	if (error == ERR_NO)
		return ("success");
	else if (error == ERR_BUILTIN_INVALID_USAGE)
		return ("usage");
	else if (error == ERR_BUILTIN_INVALID_FLAG)
		return ("invalid option");
	else if (error == ERR_INDEX_OUT_OF_BOUND)
		return ("index out of bound");
	else if (error == ERR_LIBC)
		return (strerror(errno));
	else if (error == ERR_LR_CONFLICT)
		return ("LR conflict");
	else if (error == ERR_LR_STATE_NOT_FOUND)
		return ("LR state not found");
	else if (error == ERR_OPTION_INVALID)
		return ("invalid option");
	else if (error == ERR_SHELL_NOT_FOUND)
		return ("shell data not found");
	else if (error == ERR_UNDEFINED_BEHAVIOUR)
		return ("undefined behaviour 🤪");
	else if (error == ERR_VAR_INVALID_NAME)
		return ("invalid variable name");
	else if (error == ERR_VAR_MISSING_EQUAL)
		return ("missing '='");
	else if (error == ERR_VAR_NOT_FOUND)
		return ("variable not found");
	else if (error == ERR_VAR_READ_ONLY)
		return ("readonly variable");
	return ("unknown");
}

t_error	error_print(const char *prefix, const char *error_type, t_error error)
{
	const char	*name;
	const char	*error_details;

	name = shell_get_name();
	error_details = error_to_string(error);
	(void)posix_write(STDERR_FILENO, name, str_len(name));
	(void)posix_write(STDERR_FILENO, SEPARATOR, str_len(SEPARATOR));
	if (prefix)
	{
		(void)posix_write(STDERR_FILENO, prefix, str_len(prefix));
		(void)posix_write(STDERR_FILENO, SEPARATOR, str_len(SEPARATOR));
	}
	if (error_type)
	{
		(void)posix_write(STDERR_FILENO, error_type, str_len(error_type));
		(void)posix_write(STDERR_FILENO, SEPARATOR, str_len(SEPARATOR));
	}
	(void)posix_write(STDERR_FILENO, error_details, str_len(error_details));
	(void)posix_write(STDERR_FILENO, "\n", str_len("\n"));
	return (ERR_BUILTIN_INVALID_USAGE);
}
