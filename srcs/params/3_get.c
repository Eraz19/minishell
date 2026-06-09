#include "libft.h"
#include "shell.h"

static bool	params_is_special(char name)
{
	static const char specials[] = "0$!?";

	return (str_chr(specials, name) != NULL);
}

t_error	params_get(const char *name, char **dst)
{
	t_shell		*shell;
	t_params	*params;

	shell = shell_get();
	if (!shell)
		return (ERR_SHELL_NOT_FOUND);
	params = &shell->params;
	*dst = NULL;
	if (name[0] == '\0')
		return (ERR_NO);
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
	t_shell		*shell;

	shell = shell_get();
	if (!shell)
		return (ERR_SHELL_NOT_FOUND);
	return (positionals_get(&shell->params.positionals, dst));
}

t_error	params_build_envp(char ***dst_envp)
{
	t_shell	*shell;

	shell = shell_get();
	if (!shell)
		return (ERR_SHELL_NOT_FOUND);
	return (var_build_envp(&shell->params.variables, dst_envp));
}
