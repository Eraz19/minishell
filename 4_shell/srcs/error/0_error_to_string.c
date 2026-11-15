/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_error_to_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 15:28:35 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 21:26:45 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include <string.h>

#define SEPARATOR			": "
#define WRITE_ERROR_PREFIX	"write error: "

static inline const char	*error_to_string_5(t_error err)
{
	if (err.type == ERR_INTERRUPTED)
		return ("interupted by signal");
	else if (err.type == ERR_UB)
		return ("undefined behaviour 🤪");
	else if (err.type == ERR_INTERNAL)
		return ("internal error");
	else if (err.type == ERR_LIBC)
		return (strerror(err.saved_errno));
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
	else if (err.type == ERR_POSIX_CMD_NEXC)
		return ("command not executable");
	else if (err.type == ERR_POSIX_CMD_NFOUND)
		return ("command not found");
	else if (err.type == ERR_POSIX_READ)
		return ("Unrecoverable read error");
	return ("unknown");
}

static inline const char	*error_to_string_4(t_error err)
{
	if (err.type == ERR_FILE_NOT_FOUND)
		return ("file not found");
	else if (err.type == ERR_FILE_NOT_EXECUTABLE)
		return ("file is not executable");
	else if (err.type == ERR_FILE_NOT_READABLE)
		return ("file is not readable");
	else if (err.type == ERR_POSIX_WRITE)
		return ("write error");
	else if (err.type == ERR_BUILTIN)
		return ("builtin error");
	else if (err.type == ERR_VEOF)
		return ("end of input (V)");
	else if (err.type == ERR_EOF)
		return ("end of file");
	else if (err.type == ERR_CONTINUE)
		return ("continue is only available in loops");
	else if (err.type == ERR_BREAK)
		return ("break is only available in loops");
	else if (err.type == ERR_RETURN)
		return ("return is only available in functions and dot scripts");
	else if (err.type == ERR_EXIT)
		return ("exit");
	else if (err.type == ERR_EXIT_WITH_CURRENT_STATUS)
		return ("exit with current status");
	return (error_to_string_5(err));
}

static inline const char	*error_to_string_3(t_error err)
{
	if (err.type == ERR_CTX_END_NOT_FOUND)
		return ("context end not found");
	else if (err.type == ERR_EMPTY_STACK)
		return ("empty stack");
	else if (err.type == ERR_HISTORY_DISABLED)
		return ("persistent history disabled");
	else if (err.type == ERR_NOT_IMPLEMENTED)
		return ("not implemented");
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
	else if (err.type == ERR_PID_INVALID)
		return ("invalid process or job id");
	else if (err.type == ERR_SIG_WAS_IGNORED_ON_ENTRY)
		return ("signal was ignored at entry of the non-interactive shell");
	return (error_to_string_4(err));
}

static inline const char	*error_to_string_2(t_error err)
{
	if (err.type == ERR_OPT_MISSING_ARG)
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
	return (error_to_string_3(err));
}

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
	return (error_to_string_2(err));
}
