/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:48:42 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:48:43 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_.h"

static bool	is_expansion_user_error(t_error_type type)
{
	return (type == ERR_PARAM_BAD_SUBSTITUTION
		|| type == ERR_PARAM_NULL_OR_UNSET
		|| type == ERR_VAR_INVALID_NAME
		|| type == ERR_CTX_END_NOT_FOUND);
}

t_error	expander_error_qualify(t_error err)
{
	if (err.type == ERR_NO)
		return (err);
	if (err.type == ERR_LIBC || err.type == ERR_NOT_IMPLEMENTED)
		return (error_print(err, "expander", NULL, NULL));
	if (err.type >= ERR_INTERRUPTED)
		return (err);
	if (err.type == ERR_VAR_READ_ONLY)
	{
		err = error_print(err, "expander", NULL, NULL);
		return (err.type = ERR_POSIX_ASSIGNMENT, err);
	}
	if (is_expansion_user_error(err.type))
	{
		err = error_print(err, "expander", NULL, NULL);
		return (err.type = ERR_POSIX_EXPANSION, err);
	}
	err = error_print(err, "expander", NULL, NULL);
	return (err.type = ERR_INTERNAL, err);
}
