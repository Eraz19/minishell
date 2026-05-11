#ifndef ERROR_H
# define ERROR_H

typedef enum e_error
{
	ERR_NO,
	ERR_BUILTIN_INVALID_USAGE,
	ERR_BUILTIN_INVALID_FLAG,
	ERR_INDEX_OUT_OF_BOUND,
	ERR_LIBC,
	ERR_LR_CONFLICT,
	ERR_LR_STATE_NOT_FOUND,
	ERR_OPTION_INVALID,
	ERR_SHELL_NOT_FOUND,
	ERR_UNDEFINED_BEHAVIOUR,
	ERR_VAR_INVALID_NAME,
	ERR_VAR_MISSING_EQUAL,
	ERR_VAR_NOT_FOUND,
	ERR_VAR_READ_ONLY,
	ERR_COUNT
}	t_error;

const char	*error_to_string(t_error error);

// prefix and error_type can be NULL.
// prints	"shell_name: [prefix:] [error_type:] error_details".
// e.g. 1:	"minishell: reader: unable to read: out of memory".
// e.g. 2:	"minishell: unset: my_var: readonly variable".
// Always returns error
t_error	error_print(const char *prefix, const char *error_type, t_error error);

#endif
