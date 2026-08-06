/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_ppid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:10:48 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 21:43:14 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_stubs.h"
#include "variables.h"
#include <stdlib.h>

#define PPID_NAME	"PPID"

static inline void	ppid_build_name(t_string *out)
{
	static char	name[] = PPID_NAME;
	size_t		len;

	len = sizeof(PPID_NAME) - 1;
	string_take(out, name, len + 1, (ssize_t)len);
}

t_error	var_set_ppid(void)
{
	t_string	name;
	char		*value_str;
	t_string	value;
	t_error		err;

	ppid_build_name(&name);
	value_str = ft_pidtoa(ft_getppid());
	if (!value_str)
		return (error_sys());
	if (!string_init(&value, 0, value_str, -1))
		return (err = error_sys(), free(value_str), err);
	free(value_str);
	err = var_set(&name, &value, false, false);
	string_free(&value);
	return (err);
}
