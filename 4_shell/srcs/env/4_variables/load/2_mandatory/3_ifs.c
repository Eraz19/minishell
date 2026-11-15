/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_ifs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:10:46 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 21:42:53 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variables.h"

#define IFS_NAME	"IFS"
#define IFS_VALUE	" \t\n\0"

static inline void	ifs_build_name(t_string *out)
{
	static char	name[] = IFS_NAME;
	size_t		len;

	len = sizeof(IFS_NAME) - 1;
	string_take(out, name, len + 1, (ssize_t)len);
}

static inline void	ifs_build_value(t_string *out)
{
	static char	value[] = IFS_VALUE;
	size_t		len;

	len = sizeof(IFS_VALUE) - 1;
	string_take(out, value, len + 1, (ssize_t)len);
}

t_error	var_set_ifs(void)
{
	t_string	name;
	t_string	value;

	ifs_build_name(&name);
	ifs_build_value(&value);
	return (var_set(&name, &value, false, false));
}
