/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner_handle_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:23:58 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 21:20:08 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runner_priv.h"
#include "runner_handle_errors_priv.h"
#include "options.h"

static inline void	runner_dispatch_error(
						t_runner *runner,
						t_error *err,
						bool interactive)
{
	if (err->type == ERR_EOF)
		runner_handle_eof(err, interactive);
	else if (err->type == ERR_POSIX_SYNTAX)
		runner_handle_syntax_errors(runner, err, interactive);
	else if (err->type == ERR_POSIX_READ)
		runner_handle_read_errors(err);
	else if (error_is_flow_control(*err) == true)
	{
		*err = error_print(*err, NULL, NULL);
		if (interactive == true && err->type != ERR_VEOF)
			err->type = ERR_NO;
	}
	else
		runner_handle_bad_errors(err, interactive);
	if (err->type && error_is_flow_control(*err) == false)
		*err = error_print(*err, NULL, NULL);
}

void	runner_handle_error(t_runner *runner, t_error *err)
{
	bool	interactive;
	t_error	option_err;

	if (err->type == ERR_EXIT
		|| err->type == ERR_VEOF
		|| err->type == ERR_EXIT_WITH_CURRENT_STATUS)
		return ;
	if (err->type == ERR_NOT_IMPLEMENTED)
	{
		(void)error_print(*err, NULL, NULL);
		err->type = ERR_NO;
		return ;
	}
	option_err = option_is_active(OPT_INTERACTIVE, &interactive);
	if (option_err.type)
	{
		*err = option_err;
		return ;
	}
	runner_dispatch_error(runner, err, interactive);
}
