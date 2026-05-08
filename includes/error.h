#ifndef ERROR_H
# define ERROR_H

typedef enum e_error
{
	ERR_NO,
	ERR_BUILTIN_INVALID_USAGE,
	ERR_BUILTIN_INVALID_FLAG,
	ERR_INDEX_OUT_OF_BOUND,
	ERR_INVALID_POINTER,
	ERR_LIBC,				// see errno
	ERR_VAR_INVALID_NAME,
	ERR_VAR_MISSING_EQUAL,
	ERR_VAR_NOT_FOUND,
	ERR_VAR_READ_ONLY,
	ERR_COUNT
}	t_error;

const char	*error_to_string(t_error error);
// TODO: error_print()

#endif
