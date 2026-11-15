/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 19:43:47 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 19:43:48 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include <errno.h>

t_error	error(t_error_type type)
{
	t_error	err;

	if (type == ERR_LIBC)
		return (error_sys());
	err.type = type;
	if (err.type == ERR_POSIX_WRITE)
		err.saved_errno = errno;
	else
		err.saved_errno = 0;
	err.printed = type == ERR_VEOF;
	return (err);
}

t_error	error_sys(void)
{
	t_error	err;

	err.type = ERR_LIBC;
	if (errno != 0)
		err.saved_errno = errno;
	else
		err.type = ERR_INTERNAL;
	err.printed = false;
	return (err);
}
