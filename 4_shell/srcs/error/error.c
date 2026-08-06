#include "error.h"
#include "posix_helpers.h"
#include "shell.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
# include "debug.h"	// DEBUG
#include <stdio.h>	// DEBUG
#include "logs.h"

#define SEPARATOR			": "
#define WRITE_ERROR_PREFIX	"write error" SEPARATOR

// DEBUG
t_error	error_priv(t_error_type type, const char *file, int line, const char *caller)
{
	t_error	err;

	if (type == ERR_LIBC)
		return (error_sys_priv(file, line, caller));
	err.type = type;
	if (err.type == ERR_POSIX_WRITE)
		err.saved_errno = errno;
	else
		err.saved_errno = 0;
	if (type == ERR_VEOF)
		err.printed = true;
	else
		err.printed = false;
#ifdef DEBUG_ERROR_TRACE
	if (type != ERR_NO)
		fprintf(stderr, RED "===> [ERROR] %s:%i [%s()] => %s\n" NC, 
			file, line, caller, error_to_string(err));
# else
	(void)file;
	(void)line;
	(void)caller;
#endif
	return (err);
}

// DEBUG
t_error	error_sys_priv(const char *file, int line, const char *caller)
{
	t_error	err;

	err.type = ERR_LIBC;
	if (errno != 0)
		err.saved_errno = errno;
	else
		err.type = ERR_INTERNAL;
	err.printed = false;
#ifdef DEBUG_ERROR_TRACE
	fprintf(stderr, RED "===> [ERROR] %s:%i [%s()] => ERR_LIBC (%s)\n" NC, 
		file, line, caller, error_to_string(err));
# else
	(void)file;
	(void)line;
	(void)caller;
#endif
	(void)caller;
	return (err);
}

static void	error_print_format(const char *fstring, va_list args)
{
	va_list		copy;
	t_buff		buff;
	const char	default_message[] = "(unable to compute formatted message)";

	va_copy(copy, args);
	(void)buff_init(&buff, 0, NULL, -1);
	if (buff_append_vformat(&buff, fstring, copy))
	{
		(void)posix_write(STDERR_FILENO, buff.data, buff.len);
		(void)posix_write(STDERR_FILENO, SEPARATOR, str_len(SEPARATOR));
	}
	else
		(void)posix_write(
			STDERR_FILENO,
			default_message,
			str_len(default_message));
	va_end(copy);
	buff_free(&buff);
}

t_error	error_print(t_error err, ...)
{
	va_list		args;
	const char	*shell_name;
	const char	*string;

	if (err.printed == true)
		return (err);
	shell_name = shell_get_name();
	(void)posix_write(STDERR_FILENO, shell_name, str_len(shell_name));
	(void)posix_write(STDERR_FILENO, SEPARATOR, str_len(SEPARATOR));
	va_start(args, err);
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
	if (err.type == ERR_POSIX_WRITE)
		(void)posix_write(STDERR_FILENO, WRITE_ERROR_PREFIX,
			str_len(WRITE_ERROR_PREFIX));
	string = error_to_string(err);
	(void)posix_write(STDERR_FILENO, string, str_len(string));
	(void)posix_write(STDERR_FILENO, "\n", 1);
	return (err.printed = true, err);
}

static inline int	error_priority(t_error err)
{
	if (err.type == ERR_LIBC)
		return (10);
	else if (err.type == ERR_INTERNAL)
		return (9);
	else if (err.type == ERR_UB)
		return (8);
	else if (err.type == ERR_INTERRUPTED)
		return (7);
	else if (err.type >= ERR_POSIX_SYNTAX)
		return (6);
	else if (err.type >= ERR_CONTINUE)
		return (5);
	else if (err.type >= ERR_POSIX_WRITE)
		return (4);
	else if (err.type == ERR_VEOF || err.type == ERR_EOF)
		return (2);
	else if (err.type == ERR_NO)
		return (0);
	else
		return (1);
}

t_error	error_priorize(t_error previous, t_error new)
{
	t_error	winner;
	t_error	loser;

	if (error_priority(previous) >= error_priority(new))
	{
		winner = previous;
		loser = new;
	}
	else
	{
		winner = new;
		loser = previous;

	}
#ifdef DEBUG_ERROR_TRACE
	if (previous.type != ERR_NO && new.type != ERR_NO)
		fprintf(stderr, "%s[%s] priorized against [%s]%s\n", YELLOW,
			error_to_string(winner), error_to_string(loser), NC);
# else
	(void)loser;
#endif
	return (winner);
}

t_error	error_drop_non_fatal(t_error err)
{
	bool	is_interactive;
	t_error	internal_err;

	if (err.type == ERR_NO)
		return (err);
	if (err.type < ERR_EXIT_WITH_CURRENT_STATUS)
	{
		fprintf(stderr, YELLOW "[ERROR ] non-fatal error dropped (%s)\n" NC,
			error_to_string(err));
		return (error(ERR_NO));
	}
	if (err.type == ERR_EXIT_WITH_CURRENT_STATUS || err.type == ERR_EXIT
		|| err.type == ERR_POSIX_READ || err.type == ERR_UB
		|| err.type == ERR_INTERNAL || err.type == ERR_LIBC
		|| err.type == ERR_INTERRUPTED)
		return (err);
	internal_err = option_is_active(OPT_INTERACTIVE, &is_interactive);
	if (internal_err.type)
		return (error_priorize(err, internal_err));
	if (is_interactive == true)
	{
		(void)error_print(err, NULL, NULL);
		fprintf(stderr, YELLOW "[ERROR ] non-fatal error dropped (%s)\n" NC,
			error_to_string(err));
		return (error(ERR_NO));
	}
	return (err);
}

bool	error_is_flow_control(t_error err)
{
	return (err.type >= ERR_VEOF && err.type <= ERR_INTERRUPTED);
}

t_error	err_infinite_loop(void)
{
	// TODO print xav BG face
	return (error(ERR_VEOF));
}
