#include "libft.h"
#include "shell.h"

static bool	params_is_special(char name)
{
	static const char specials[] = "0$!?";

	return (str_chr(specials, name) != NULL);
}

t_error	params_get(const char *name, char **dst)
{
	t_params	*params;

	*dst = NULL;
	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	if (name[0] == '\0')
		return (error(ERR_NO));
	if (name[0] == '-' && name[1] == '\0')
		return (options_get(params->options, dst));
	if (name[0] == '#' && name[1] == '\0')
		return (positionals_get_one(&params->positionals, name, dst));
	if (name[1] == '\0' && params_is_special(name[0]))
		return (specials_get(&params->specials, name[0], dst));
	if (ft_isdigit(name[0]))
		return (positionals_get_one(&params->positionals, name, dst));
	return (var_get(name, dst));
}

t_error	params_get_positionals(t_positionals *dst)
{
	t_params	*params;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	return (positionals_get(&params->positionals, dst));
}

t_error	params_build_envp(char ***dst_envp)
{
	t_params	*params;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	return (var_build_envp(&params->variables, dst_envp));
}
