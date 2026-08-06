/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_runner_handle_errors_helpers.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:23:58 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 21:16:34 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runner_handle_errors_priv.h"
#include "parser.h"
#include "env.h"

void	runner_handle_eof(t_error *err, bool interactive)
{
	if (interactive == true)
		err->type = ERR_NO;
}

void	runner_handle_syntax_errors(
						t_runner *runner,
						t_error *err,
						bool interactive)
{
	*err = error_print(*err, NULL, NULL);
	(void)env_set_last_status((int)err->type);
	if (interactive == true)
	{
		parser_clear(&runner->parser);
		err->type = ERR_NO;
	}
}

void	runner_handle_read_errors(t_error *err)
{
	*err = error_print(*err, NULL, NULL);
	(void)env_set_last_status((int)err->type);
}

void	runner_handle_bad_errors(t_error *err, bool interactive)
{
	if (err->type == ERR_NO || err->type == ERR_POSIX_READ)
		return ;
	if (err->type >= ERR_VEOF
		&& (err->type <= ERR_LIBC || interactive == false))
		return ;
}
