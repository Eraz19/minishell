#include <stddef.h>
#include "heredoc_.h"

static bool	is_expansion_user_error(t_error_type type)
{
	return (type == ERR_PARAM_BAD_SUBSTITUTION
		|| type == ERR_PARAM_NULL_OR_UNSET
		|| type == ERR_QUOTED_TILDE);
}

t_error	heredoc_error_qualify(t_error err)
{
	if (err.type == ERR_NO)
		return (err);
	if (err.type == ERR_LIBC)
		return (error_print(err, "heredoc", NULL, NULL));
	if (err.type >= ERR_INTERRUPTED)
		return (err);
	if (err.type == ERR_POSIX_WRITE || err.type == ERR_REDIRECTION)
		return (err.type = ERR_REDIRECTION, err);
	if (is_expansion_user_error(err.type))
	{
		err = error_print(err, "heredoc", NULL, NULL);
		return (err.type = ERR_POSIX_EXPANSION, err);
	}
	err = error_print(err, "heredoc", NULL, NULL);
	return (err.type = ERR_INTERNAL, err);
}
