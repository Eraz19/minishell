#include "libft.h"
#include "shell.h"
# include <assert.h>	// DEBUG

static bool	params_is_special(char name)
{
	static const char specials[] = "0$!?";

	return (str_chr(specials, name) != NULL);
}

t_error	params_get(const t_string *name, t_string *dst)
{
	t_params	*params;

	assert(name != NULL);
	assert(name->data != NULL);
	assert(name->data[0] != '\0');
	assert(name->len > 0);
	assert(dst != NULL);
	(void)string_init(dst, 0, NULL, 0);
	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	if (name->data[0] == '\0')
		return (error(ERR_NO));
	if (name->data[0] == '-' && name->data[1] == '\0')
		return (options_get(params->options, dst));
	if (name->data[0] == '#' && name->data[1] == '\0')
		return (positionals_get_one(&params->positionals_stack, name, dst));
	if (name->data[1] == '\0' && params_is_special(name->data[0]))
		return (specials_get(&params->specials, name->data[0], dst));
	if (ft_isdigit(name->data[0]))
		return (positionals_get_one(&params->positionals_stack, name, dst));
	return (var_get(name, dst));
}

t_error	params_get_from_const(const char *name, t_string *dst)
{
	t_params	*params;

	assert(name != NULL);
	assert(name[0] != '\0');
	assert(dst != NULL);
	(void)string_init(dst, 0, NULL, 0);
	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	if (name[0] == '\0')
		return (error(ERR_NO));
	if (name[0] == '-' && name[1] == '\0')
		return (options_get(params->options, dst));
	if (name[0] == '#' && name[1] == '\0')
		return (positionals_get_one_cst(&params->positionals_stack, name, dst));
	if (name[1] == '\0' && params_is_special(name[0]))
		return (specials_get(&params->specials, name[0], dst));
	if (ft_isdigit(name[0]))
		return (positionals_get_one_cst(&params->positionals_stack, name, dst));
	return (var_get_from_const(name, dst));
}

t_error	params_get_positionals(const t_positionals **dst)
{
	t_params	*params;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	return (positionals_get(&params->positionals_stack, dst));
}

t_error	params_build_envp(char ***dst_envp)
{
	t_params	*params;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	return (var_build_envp(&params->variables, dst_envp));
}
