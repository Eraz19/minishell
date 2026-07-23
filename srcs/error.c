#include "error.h"
#include "posix_helpers.h"
#include "shell.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
# include <debug.h>	// DEBUG
#include <stdio.h>	// DEBUG
#include "logs.h"

#define SEPARATOR			": "
#define WRITE_ERROR_PREFIX	"write error" SEPARATOR

// TODO: split in 2 functions and move to another file
const char	*error_to_string(t_error err)
{
	if (err.type == ERR_NO)
		return ("success");
	else if (err.type == ERR_ASSIGNMENT_MISSING_NAME)
		return ("missing assignment name");
	else if (err.type == ERR_INVALID_USAGE)
		return ("invalid usage");
	else if (err.type == ERR_FD_INVALID)
		return ("invalid file descriptor");
	else if (err.type == ERR_HOOK_INVALID_RHS_LEN)
		return ("invalid rhs len");
	else if (err.type == ERR_INDEX_OUT_OF_BOUND)
		return ("index out of bound");
	else if (err.type == ERR_FORMAT_INVALID)
		return ("invalid format");
	else if (err.type == ERR_LR_CONFLICT)
		return ("LR conflict");
	else if (err.type == ERR_LR_STATE_NOT_FOUND)
		return ("LR state not found");
	else if (err.type == ERR_INVALID_USAGE)
		return ("invalid open() usage");
	else if (err.type == ERR_OPT_INVALID)
		return ("invalid option");
	else if (err.type == ERR_OPT_INVALID_ARG)
		return ("invalid option argument");
	else if (err.type == ERR_OPT_MISSING_ARG)
		return ("missing option argument");
	else if (err.type == ERR_PARSER_EMPTY_GOTO)
		return ("empty goto");
	else if (err.type == ERR_PARSER_INVALID_FUNCTION_NAME)
		return ("invalid function name");
	else if (err.type == ERR_PARSER_INVALID_STATE)
		return ("invalid state");
	else if (err.type == ERR_REDIRECTION)
		return ("redirection failed");
	else if (err.type == ERR_SHELL_NOT_FOUND)
		return ("shell data not found");
	else if (err.type == ERR_SHIFT_INVALID_VALUE)
		return ("is greater than $#");
	else if (err.type == ERR_SIZE_MAX_REACHED)
		return ("SIZE_MAX has been reached");
	else if (err.type == ERR_VAR_INVALID_NAME)
		return ("invalid name");
	else if (err.type == ERR_VAR_MISSING_EQUAL)
		return ("missing '='");
	else if (err.type == ERR_VAR_NOT_FOUND)
		return ("not found");
	else if (err.type == ERR_VAR_READ_ONLY)
		return ("readonly variable");
	else if (err.type == ERR_CTX_END_NOT_FOUND)
		return ("context end not found");
	else if (err.type == ERR_EMPTY_STACK)
		return ("empty stack");
	else if (err.type == ERR_HISTORY_DISABLED)
		return ("persistent history disabled");
	else if (err.type == ERR_INCOHERENT_STATE)
		return ("incoherent state");
	else if (err.type == ERR_NOT_IMPLEMENTED)
		return ("not implemented");
	else if (err.type == ERR_UNEXPECTED_EOI)
		return ("unexpected end of input");
	else if (err.type == ERR_NO_DELIM)
		return ("missing delimiter");
	else if (err.type == ERR_NO_INPUT_TO_LEX)
		return ("no input_to lex");
	else if (err.type == ERR_QUOTED_TILDE)
		return ("quoted tilde");
	else if (err.type == ERR_EXP_RESULT_INCOHERENT)
		return ("expansion generated an expected result (more/less fields)");
	else if (err.type == ERR_PARAM_NULL_OR_UNSET)
		return ("parameter null or not set");
	else if (err.type == ERR_PARAM_BAD_SUBSTITUTION)
		return ("bad substitution");
	else if (err.type == ERR_ALIAS_INVALID_NAME)
		return ("invalid alias name");
	else if (err.type == ERR_ALIAS_NOT_FOUND)
		return ("not found");
	else if (err.type == ERR_PID_INVALID)
		return ("invalid process or job id");
	else if (err.type == ERR_SIG_WAS_IGNORED_ON_ENTRY)
		return ("signal was ignored at entry of the non-interactive shell");
	// posix_write() error
	else if (err.type == ERR_POSIX_WRITE)
		return ("write error");
	// builtin errors
	else if (err.type == ERR_BUILTIN)
		return ("builtin error");
	// Flow control errors
	else if (err.type == ERR_VEOF)
		return ("end of input");
	else if (err.type == ERR_EOF)
		return ("end of file");
	else if (err.type == ERR_CONTINUE)
		return ("continue is only available in loops");
	else if (err.type == ERR_BREAK)
		return ("break is only available in loops");
	else if (err.type == ERR_RETURN)
		return ("return is only available in functions");
	else if (err.type == ERR_EXIT)
		return ("exit");
	else if (err.type == ERR_EXIT_WITH_CURRENT_STATUS)
		return ("exit with current status");
	else if (err.type == ERR_INTERRUPTED)
		return ("interupted by signal");
	else if (err.type == ERR_UB)
		return ("undefined behaviour 🤪");
	// Internal errors
	else if (err.type == ERR_INTERNAL)
		return ("internal error");
	else if (err.type == ERR_LIBC)
		return (strerror(err.saved_errno));
	// POSIX errors
	else if (err.type == ERR_POSIX_SYNTAX)
		return ("invalid syntax");
	else if (err.type == ERR_POSIX_BUILTIN_SPECIAL)
		return ("special builtin error");
	else if (err.type == ERR_POSIX_REDIR_SPECIAL)
		return ("redirection error (special built-in)");
	else if (err.type == ERR_POSIX_ASSIGNMENT)
		return ("variable assignment error");
	else if (err.type == ERR_POSIX_EXPANSION)
		return ("expansion error");
	else if (err.type == ERR_POSIX_CMD_NOT_EXECUTABLE)
		return ("command not executable");
	else if (err.type == ERR_POSIX_CMD_NOT_FOUND)
		return ("command not found");
	else if (err.type == ERR_POSIX_READ)
		return ("Unrecoverable read error");
	return ("unknown");
}

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
