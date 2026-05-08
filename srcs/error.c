#include "error.h"
#include <errno.h>
#include <string.h>

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
	else if (error == ERR_INVALID_POINTER)
		return ("invalid pointer");
	else if (error == ERR_LIBC)
		return (strerror(errno));
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
