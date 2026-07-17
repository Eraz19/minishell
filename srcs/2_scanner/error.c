#include "scanner_.h"

static bool	is_unexpected_end_of_input(t_error_type type)
{
	return (type == ERR_VEOF
		|| type == ERR_UNEXPECTED_EOI
		|| type == ERR_CTX_END_NOT_FOUND
		|| type == ERR_NO_DELIM
		|| type == ERR_REDIRECTION);
}

t_error	scanner_error_qualify(t_error err, bool allow_veof)
{
	if (err.type == ERR_NO || (err.type == ERR_VEOF && allow_veof))
		return (err);
	if (err.type == ERR_LIBC)
		return (error_print(err, "scanner", NULL, NULL));
	if (err.type >= ERR_INTERRUPTED)
		return (err);
	if (is_unexpected_end_of_input(err.type))
	{
		if (err.type == ERR_VEOF)
			err.printed = false;
		err = error_print(err, "scanner", NULL, NULL);
		return (err.type = ERR_POSIX_SYNTAX, err);
	}
	err = error_print(err, "scanner", NULL, NULL);
	return (err.type = ERR_INTERNAL, err);
}
