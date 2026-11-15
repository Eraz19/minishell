/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_get.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:11:05 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:51:49 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "variables.h"
#include "variables_priv.h"
#include "utils.h"
#include "grammar_name.h"
#include <stdlib.h>

// @ret ERR_VAR_NOT_FOUND / ERR_LIBC
static inline t_error	var_get_priv(const char *name, t_string *dst_val)
{
	t_params	*params;
	const t_var	*var;

	params = shell_get_params();
	var = hashmap_get_const(&params->variables, name);
	if (var == NULL)
		return (error(ERR_VAR_NOT_FOUND));
	if (!string_dup(dst_val, &var->value))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	var_get(const t_string *name, t_string *dst_val)
{
	if (!name_is_valid_str(name))
		return (error(ERR_VAR_INVALID_NAME));
	return (var_get_priv(name->data, dst_val));
}

t_error	var_get_from_const(const char *name, t_string *dst_val)
{
	if (!name_is_valid(name))
		return (error(ERR_VAR_INVALID_NAME));
	return (var_get_priv(name, dst_val));
}
