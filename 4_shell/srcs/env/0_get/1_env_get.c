/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_env_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:14:54 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 17:24:14 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include <assert.h>	// DEBUG

#define SPECIALS	"0$!?"

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
	assert(params != NULL);
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
