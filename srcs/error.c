#include "error.h"
#include "posix_helpers.h"
#include "shell.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

#define SEPARATOR		": "

// TODO: split in 2 functions and move to another file
static const char	*error_to_string(t_error_type error, int saved_errno)
{
	if (error == ERR_NO)
		return ("success");
	else if (error == ERR_ASSIGNMENT_MISSING_NAME)
		return ("missing assignment name");
	else if (error == ERR_BUILTIN_INVALID_USAGE)
		return ("usage");
	else if (error == ERR_INDEX_OUT_OF_BOUND)
		return ("index out of bound");
	else if (error == ERR_INVALID_FORMAT)
		return ("invalid format");
	else if (error == ERR_LIBC)
		return (strerror(saved_errno));
	else if (error == ERR_LR_CONFLICT)
		return ("LR conflict");
	else if (error == ERR_LR_STATE_NOT_FOUND)
		return ("LR state not found");
	else if (error == ERR_OPT_INVALID)
		return ("invalid option");
	else if (error == ERR_OPT_INVALID_ARG)
		return ("invalid option argument");
	else if (error == ERR_OPT_MISSING_ARG)
		return ("missing option argument");
	else if (error == ERR_SHELL_NOT_FOUND)
		return ("shell data not found");
	else if (error == ERR_SHIFT_INVALID_VALUE)
		return ("shift value is out of range");
	else if (error == ERR_SIZE_MAX_REACHED)
		return ("SIZE_MAX has been reached");
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

t_error	error(t_error_type type)
{
	return ((t_error)
	{
		.type = type,
		.saved_errno = 0
	});
}

t_error	error_sys()
{
	return ((t_error)
	{
		.type = ERR_LIBC,
		.saved_errno = errno
	});
}

static void	error_print_format(const char *fstring, va_list args)
{
	va_list	copy;
	t_buff	buff;

	va_copy(copy, args);
	(void)buff_init(&buff, 0, NULL, -1);
	if (buff_append_vformat(&buff, fstring, copy))
	{
		(void)posix_write(STDERR_FILENO, buff.data, buff.len);
		(void)posix_write(STDERR_FILENO, SEPARATOR, str_len(SEPARATOR));
	}
	va_end(copy);
	buff_free(&buff);
}

t_error	error_print(t_error error, ...)
{
	va_list		args;
	const char	*shell_name;
	const char	*string;

	shell_name = shell_get_name();
	(void)posix_write(STDERR_FILENO, shell_name, str_len(shell_name));
	(void)posix_write(STDERR_FILENO, SEPARATOR, str_len(SEPARATOR));
	va_start(args, error);
	string = va_arg(args, const char *);
	while (string)
	{
		(void)posix_write(STDERR_FILENO, string, str_len(string));
		(void)posix_write(STDERR_FILENO, SEPARATOR, str_len(SEPARATOR));
		string = va_arg(args, const char *);
	}
	string = va_arg(args, const char *);
	if (string)
		error_print_format(string, args);
	va_end(args);
	string = error_to_string(error.type, error.saved_errno);
	(void)posix_write(STDERR_FILENO, string, str_len(string));
	(void)posix_write(STDERR_FILENO, "\n", 1);
	return (error);
}
