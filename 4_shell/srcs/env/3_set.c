/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_set.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:14:56 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 21:47:27 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_error	env_set_variable(
	const t_string *name,
	const t_string *value,
	bool export,
	bool readonly)
{
	t_error	err;

	err = var_set(name, value, export, readonly);
	if (err.type)
	{
		err = error_print(err, NULL, "%s", name->data, NULL);
		if (err.type != ERR_LIBC)
			err.type = ERR_POSIX_ASSIGNMENT;
	}
	return (err);
}

t_error	env_unset_variable(const t_string *name)
{
	return (var_unset(name));
}

void	env_set_last_status_in(t_params *params, int value)
{
	specials_set_last_status(&params->specials, value);
}

t_error	env_set_last_status(int value)
{
	t_params	*params;

	params = shell_get_params();
	env_set_last_status_in(params, value);
	return (error(ERR_NO));
}

t_error	env_set_option(t_option option, bool on)
{
	t_params	*params;

	params = shell_get_params();
	option_set(&params->options, option, on);
	return (error(ERR_NO));
}
