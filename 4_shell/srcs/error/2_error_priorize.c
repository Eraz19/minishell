/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_error_priorize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 19:53:01 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 19:53:02 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

static inline int	error_priority(t_error err)
{
	if (err.type == ERR_LIBC)
		return (10);
	else if (err.type == ERR_INTERNAL)
		return (9);
	else if (err.type == ERR_UB)
		return (8);
	else if (err.type == ERR_INTERRUPTED)
		return (7);
	else if (err.type >= ERR_POSIX_SYNTAX)
		return (6);
	else if (err.type >= ERR_CONTINUE)
		return (5);
	else if (err.type >= ERR_POSIX_WRITE)
		return (4);
	else if (err.type == ERR_VEOF || err.type == ERR_EOF)
		return (2);
	else if (err.type == ERR_NO)
		return (0);
	else
		return (1);
}

t_error	error_priorize(t_error previous, t_error new)
{
	if (error_priority(previous) >= error_priority(new))
		return (previous);
	return (new);
}
