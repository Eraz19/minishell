/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:48:12 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:43:18 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

t_error	assignment_split(
			const char *src,
			t_string *dst_name,
			t_string *dst_value)
{
	size_t	len;
	bool	has_equal;
	t_error	err;

	(void)string_init(dst_name, 0, NULL, 0);
	(void)string_init(dst_value, 0, NULL, 0);
	len = 0;
	while (src[len] && src[len] != '=')
		len++;
	if (len == 0)
		return (error(ERR_ASSIGNMENT_MISSING_NAME));
	has_equal = src[len] == '=';
	if (!string_append_n(dst_name, src, (long)len))
		return (error_sys());
	if (!has_equal)
		return (error(ERR_NO));
	if (!string_append_n(dst_value, src + len + 1, -1))
		return (err = error_sys(), string_free(dst_name), err);
	return (error(ERR_NO));
}
