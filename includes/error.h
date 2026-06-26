#ifndef ERROR_H
# define ERROR_H

#include <stdbool.h>

# define error(type) error_priv(type, __func__)
# define error_sys(type) error_sys_priv(__func__)

typedef enum e_error_type
{
	ERR_NO,
	ERR_ASSIGNMENT_MISSING_NAME,
	ERR_BUILTIN_INVALID_USAGE,
	ERR_HOOK_INVALID_RHS_LEN,
	ERR_INDEX_OUT_OF_BOUND,
	ERR_INVALID_FORMAT,
	ERR_LIBC,
	ERR_LR_CONFLICT,
	ERR_LR_STATE_NOT_FOUND,
	ERR_OPT_INVALID,
	ERR_OPT_INVALID_ARG,
	ERR_OPT_MISSING_ARG,
	ERR_PARSER_EMPTY_GOTO,
	ERR_PARSER_INVALID_FUNCTION_NAME,
	ERR_PARSER_INVALID_STATE,
	ERR_SHELL_NOT_FOUND,
	ERR_SHIFT_INVALID_VALUE,
	ERR_SIZE_MAX_REACHED,
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
	ERR_INCOHERENT_STATE,
	ERR_NOT_IMPLEMENTED,
	ERR_HEREDOC_FILE_LIMIT,
	ERR_UNEXPECTED_EOI,
	ERR_NO_DELIM,
	ERR_COUNT
}	t_error_type;

typedef struct s_error
{
	t_error_type	type;
	int				saved_errno;
	bool			printed;
}	t_error;

/**
 * @brief Builds an error descriptor from an internal error type.
 *
 * The saved errno value is set to 0.
 *
 * @warning Use error_sys() instead when the error comes from a failed libc or
 * POSIX call and errno must be preserved.
 *
 * @param type Error type to store.
 * @return Error descriptor containing type and no saved errno.
 */
t_error	error_priv(t_error_type type, const char *caller);

/**
 * @brief Builds a libc error descriptor and saves the current errno value.
 *
 * This function must be called immediately after a failed libc or POSIX call,
 * before any other call can overwrite errno.
 *
 * @return Error descriptor containing ERR_LIBC and the current errno value.
 */
t_error	error_sys_priv(const char *caller);

/**
 * @brief Prints a formatted shell error message to stderr.
 *
 * The shell name prefix is printed automatically by this function, since its value
 * depends on the current shell context. Additional prefixes passed by the caller
 * are printed after it, in order, and separated with ": ".
 *
 * The variadic argument list must follow this exact layout:
 * prefixes..., NULL, fstring, fstring arguments...
 *
 * The NULL separator marks the end of the caller-provided prefix list. If fstring
 * is not NULL, it is used as a printf-like format string and must be followed by
 * the matching arguments. If fstring is NULL, no format arguments are read.
 *
 * Example:
 * error_print(error(ERR_OPT_INVALID), "export", "-x", NULL, "%i", my_integer);
 *
 * @warning The caller-provided prefix list must always be terminated by NULL.
 * @warning fstring arguments must match the conversion specifiers used by fstring.
 *
 * @param error Error descriptor to print and return.
 * @param ... Additional prefixes, NULL separator, optional format string, optional arguments.
 * @return The error descriptor received as argument.
 */
t_error	error_print(t_error err, ...);

const char	*error_to_string(t_error err);

// @ret ERR_UNDEFINED_BEHAVIOUR
t_error	undefined_behaviour(const char *message);

#endif
