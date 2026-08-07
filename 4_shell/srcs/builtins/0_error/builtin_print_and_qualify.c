/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_print_and_qualify.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:40:36 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:33:42 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_error.h"
#include <stdlib.h>

t_error	builtin_print_and_qualify(
			const char *builtin_name,
			t_error err,
			bool is_special_builtin,
			int *status)
{
	if (*status < 0)
		*status = (int)err.type;
	if (err.type == ERR_NO)
		return (err);
	err = error_print(err, builtin_name, NULL, NULL);
	if (err.type != ERR_INTERNAL && err.type != ERR_LIBC)
	{
		if (is_special_builtin == true)
			err.type = ERR_POSIX_BUILTIN_SPECIAL;
		else
			err.type = ERR_BUILTIN;
	}
	return (err);
}
