/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_get.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:14:54 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 15:17:33 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include <assert.h>	// DEBUG

#define SPECIALS	"0$!?"

// TODO: refactor
static inline t_error	env_get_struct(t_params **dst)
{
	t_error	err;

	*dst = shell_get_params();
	if (*dst == NULL)
	{
		err = error_print(error(ERR_SHELL_NOT_FOUND), "params", NULL, NULL);
		err.type = ERR_INTERNAL;
		return (err);
	}
	return (error(ERR_NO));
}

t_error	env_get(const t_string *name, t_string *dst)
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
	if (name->data[1] == '\0' && str_chr(SPECIALS, name->data[0]) != NULL)
		return (specials_get(&params->specials, name->data[0], dst));
	if (ft_isdigit(name->data[0]))
		return (positionals_get_one(&params->positionals_stack, name, dst));
	return (var_get(name, dst));
}

t_error	env_get_from_const(const char *name, t_string *dst)
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
	if (name[1] == '\0' && str_chr(SPECIALS, name[0]) != NULL)
		return (specials_get(&params->specials, name[0], dst));
	if (ft_isdigit(name[0]))
		return (positionals_get_one_cst(&params->positionals_stack, name, dst));
	return (var_get_from_const(name, dst));
}

t_error	env_get_positionals(const t_positionals **dst)
{
	t_params	*params;
	t_error		err;

	err = env_get_struct(&params);
	if (err.type)
		return (err);
	return (positionals_get(&params->positionals_stack, dst));
}

t_error	env_build_envp(t_vector *dst_envp)
{
	t_params	*params;
	t_error		err;

	err = env_get_struct(&params);
	if (err.type)
		return (err);
	return (var_build_envp(&params->variables, dst_envp));
}

int	env_get_last_status_from(t_params *params)
{
	return (params->specials.last_status);
}

t_error	env_get_last_status(int *out)
{
	t_params	*params;
	t_error		err;

	err = env_get_struct(&params);
	if (err.type)
		return (err);
	*out = env_get_last_status_from(params);
	return (err);
}

t_error	env_get_cmd_cache(t_cmd_cache **out_cmd_cache_ptr)
{
	t_params	*params;
	t_error		err;

	err = env_get_struct(&params);
	if (err.type)
		return (err);
	*out_cmd_cache_ptr = &params->cmd_cache;
	return (err);
}

t_error	env_get_fd_manager(t_fd_manager **out_fd_manager_ptr)
{
	t_params	*params;
	t_error		err;

	err = env_get_struct(&params);
	if (err.type)
		return (err);
	*out_fd_manager_ptr = &params->fd_manager;
	return (err);
}

t_error	env_get_source(const t_string **source)
{
	t_params	*params;
	t_error		err;

	err = env_get_struct(&params);
	if (err.type)
		return (err);
	*source = &params->specials.source;
	return (err);
}
