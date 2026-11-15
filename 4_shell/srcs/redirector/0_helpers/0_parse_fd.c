/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_parse_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 15:20:18 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 15:20:19 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirector_priv.h"
#include <limits.h>

bool	redirect_parse_fd(const char *s, int *out_fd)
{
	long	result;

	*out_fd = -1;
	if (*s == '\0')
		return (false);
	result = 0;
	while (*s)
	{
		if (*s < '0' || *s > '9' || result > (INT_MAX - (*s - '0')) / 10)
			return (false);
		result = result * 10 + (*s - '0');
		s++;
	}
	*out_fd = (int)result;
	return (true);
}
