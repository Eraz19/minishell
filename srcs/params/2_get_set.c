#include "libft.h"
#include "params.h"
#include <stdbool.h>

static bool	params_is_special(char name)
{
	static const char specials[] = "0@*#$!?";

	return (str_chr(specials, name) != NULL);
}

// @ret ERR_VAR_NOT_FOUND / ERR_LIBC.
t_error	params_get(t_params *params, const char *name, char **dst)
{
	if (name[0] == '\0')
	{
		*dst = NULL;
		return (ERR_NO);
	}
	if (name[0] == '-' && name[1] == '\0')
		return (options_to_string(params->options, dst));
	if (name[1] == '\0' && params_is_special(name[0]))
	{
		*dst = specials_get(name[0]);
		return (ERR_NO);
	}
	return (var_get(&params->variables, name, dst));
}

t_error	params_set_variable(const char *name, const char *value)
{

}

t_error	params_set_option(const char *name, const char *value)
{

}
