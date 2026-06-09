#ifndef ERROR_H
# define ERROR_H

typedef enum e_error
{
	ERR_NO,
	ERR_SIZE_MAX_REACHED,
	ERR_BUILTIN_INVALID_USAGE,
	ERR_BUILTIN_INVALID_FLAG,
	ERR_INDEX_OUT_OF_BOUND,
	ERR_LIBC,
	ERR_LR_CONFLICT,
	ERR_LR_STATE_NOT_FOUND,
	ERR_OPT_INVALID,
	ERR_OPT_INVALID_ARG,
	ERR_OPT_MISSING_ARG,
	ERR_SHELL_NOT_FOUND,
	ERR_SHIFT_INVALID_VALUE,
	ERR_UNDEFINED_BEHAVIOUR,
	ERR_VAR_INVALID_NAME,
	ERR_VAR_MISSING_EQUAL,
	ERR_VAR_NOT_FOUND,
	ERR_VAR_READ_ONLY,
	// Lexer
	ERR_NULL_ARGS,
	ERR_TOKEN_INIT,
	ERR_CTX_END_NOT_FOUND,
	ERR_VALUE_OUT_OF_RANGE,
	ERR_LEX_INCOMPLETE,
	ERR_INVALID_SYNTAX,
	ERR_EMPTY_STACK,
	ERR_VEOF,
	ERR_EMPTY_CONTINUATION,
	ERR_INVALID_ARGS,
	ERR_FILE_STAT,
	ERR_OPEN_FILE,
	ERR_INCOHERENT_STATE,
	ERR_NOT_IMPLEMENTED,
	ERR_HEREDOC_FILE_LIMIT,
	ERR_UNEXPECTED_EOI,
	ERR_NO_DELIM,

	ERR_COUNT
}	t_error;

const char	*error_to_string(t_error error);

// prefix and error_type can be NULL.
// prints	"shell_name: [prefix:] [error_type:] error_details".
// e.g. 1:	"minishell: reader: unable to read: out of memory".
// e.g. 2:	"minishell: unset: my_var: readonly variable".
// Always returns error
t_error	error_print(const char *prefix, const char *error_type, t_error error);

// Prints "you did: " + message + "la tête à Xavier"
void	undefined_behaviour(const char *message);

#endif
