/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_error_drop_non_fatal.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 19:52:58 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 19:52:59 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "options.h"

t_error	error_drop_non_fatal(t_error err)
{
	bool	is_interactive;
	t_error	internal_err;

	if (err.type == ERR_NO)
		return (err);
	if (err.type < ERR_EXIT_WITH_CURRENT_STATUS)
		return (error(ERR_NO));
	if (err.type == ERR_EXIT_WITH_CURRENT_STATUS || err.type == ERR_EXIT
		|| err.type == ERR_POSIX_READ || err.type == ERR_UB
		|| err.type == ERR_INTERNAL || err.type == ERR_LIBC
		|| err.type == ERR_INTERRUPTED)
		return (err);
	internal_err = option_is_active(OPT_INTERACTIVE, &is_interactive);
	if (internal_err.type)
		return (error_priorize(err, internal_err));
	if (is_interactive == true)
	{
		(void)error_print(err, NULL, NULL);
		return (error(ERR_NO));
	}
	return (err);
}
