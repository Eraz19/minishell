/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:23:16 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 21:26:45 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdbool.h>

# define ERR_POSIX_SIGNAL_BASE_CODE	128

typedef enum e_error_type
{
	ERR_NO,
	ERR_ASSIGNMENT_MISSING_NAME,
	ERR_FD_INVALID,
	ERR_FORMAT_INVALID,
	ERR_HOOK_INVALID_RHS_LEN,
	ERR_INDEX_OUT_OF_BOUND,
	ERR_LR_CONFLICT,
	ERR_LR_STATE_NOT_FOUND,
	ERR_PARSER_EMPTY_GOTO,
	ERR_PARSER_INVALID_FUNCTION_NAME,
	ERR_PARSER_INVALID_STATE,
	ERR_SHELL_NOT_FOUND,
	ERR_SHIFT_INVALID_VALUE,
	ERR_SIZE_MAX_REACHED,
	ERR_VAR_INVALID_NAME,
	ERR_VAR_MISSING_EQUAL,
	ERR_VAR_NOT_FOUND,
	ERR_VAR_READ_ONLY,
	ERR_CTX_END_NOT_FOUND,
	ERR_EMPTY_STACK,
	ERR_HISTORY_DISABLED,
	ERR_NO_DELIM,
	ERR_NOT_IMPLEMENTED,
	ERR_NO_INPUT_TO_LEX,
	ERR_EXP_RESULT_INCOHERENT,
	ERR_QUOTED_TILDE,
	ERR_PARAM_NULL_OR_UNSET,
	ERR_PARAM_BAD_SUBSTITUTION,
	ERR_SIG_WAS_IGNORED_ON_ENTRY,
	ERR_PID_INVALID,
	ERR_FILE_NOT_FOUND,
	ERR_FILE_NOT_EXECUTABLE,
	ERR_FILE_NOT_READABLE,
	ERR_OPT_INVALID,
	ERR_OPT_INVALID_ARG,
	ERR_OPT_MISSING_ARG,
	ERR_POSIX_WRITE = 90,
	ERR_INVALID_USAGE = 91,
	ERR_REDIRECTION = 92,
	ERR_BUILTIN = 93,
	ERR_VEOF = 100,
	ERR_EOF = 101,
	ERR_CONTINUE = 102,
	ERR_BREAK = 103,
	ERR_RETURN = 104,
	ERR_EXIT_WITH_CURRENT_STATUS = 105,
	ERR_EXIT = 106,
	ERR_INTERRUPTED = 107,
	ERR_UB = 108,
	ERR_INTERNAL = 110,
	ERR_LIBC = 111,
	ERR_POSIX_SYNTAX = 121,
	ERR_POSIX_BUILTIN_SPECIAL = 122,
	ERR_POSIX_REDIR_SPECIAL = 123,
	ERR_POSIX_ASSIGNMENT = 124,
	ERR_POSIX_EXPANSION = 125,
	ERR_POSIX_CMD_NEXC = 126,
	ERR_POSIX_CMD_NFOUND = 127,
	ERR_POSIX_READ = 128
}	t_error_type;

typedef struct s_error
{
	t_error_type	type;
	int				saved_errno;
	bool			printed;
}	t_error;

t_error		error(t_error_type type);
t_error		error_sys(void);
t_error		error_print(t_error err, ...);
t_error		error_priorize(t_error previous, t_error new);
const char	*error_to_string(t_error err);
t_error		undefined_behaviour(const char *message);
void		print_unspecified_behaviour(
				const char *optional_prefix,
				const char *posix_citation,
				const char *implemented_as);
t_error		error_drop_non_fatal(t_error err);
bool		error_is_flow_control(t_error err);
t_error		error_infinite_loop(void);

#endif
