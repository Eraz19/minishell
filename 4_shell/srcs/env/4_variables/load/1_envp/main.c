/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:10:38 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 15:03:44 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variables.h"
#include "utils.h"
#include <stdlib.h>
#include "logs.h"		// DEBUG
#include <assert.h>	// DEBUG

// @ret ERR_LIBC.
static inline t_error	process_entry(t_string *name, t_string *value)
{
	t_error	err;

	if (value->data == NULL)
		return (error(ERR_NO));
	err = var_set(name, value, true, false);
	if (err.type == ERR_VAR_INVALID_NAME || err.type == ERR_VAR_READ_ONLY)
		return (error(ERR_NO));
	return (err);
}

/*
1. Load envp variables with valid shell names
	- exported = true
	- readonly = false
	- invalid names: do not initialize shell variables from them
*/
t_error	var_load_envp(char **envp)
{
	size_t		i;
	t_string	name;
	t_string	value;
	t_error		err;

	if (!envp)
		return (error(ERR_NO));
	i = 0;
	err = error(ERR_NO);
	while (envp[i] && err.type == ERR_NO)
	{
		err = assignment_split(envp[i], &name, &value);
		if (err.type)
			return (err);
		err = process_entry(&name, &value);
		string_free(&name);
		string_free(&value);
		i++;
	}
	print_pass("variables loaded from env              %i\n", (int)i);
	return (err);
}
