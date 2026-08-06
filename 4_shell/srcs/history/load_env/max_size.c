/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:09:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/05 19:05:14 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "debug.h"
#include "history_load_env.h"
#include "history_load_env_priv.h"

void	load_max_size_unset_value(t_history *history)
{
	history->adapter.max = -1;
	history_load_max_size_from_unset_logs();
}

void	load_max_size_invalid_value(t_history *history)
{
	history->adapter.max = -1;
	history_load_max_size_from_invalid_logs();
}

t_error	load_history_max_size_env(t_history *history)
{
	long		max;
	t_string	max_str;

	history->err = env_get_from_const("HISTSIZE", &max_str);
	if (history->err.type && history->err.type != ERR_VAR_NOT_FOUND)
		return (history->err);
	if (history->err.type == ERR_VAR_NOT_FOUND || max_str.len == 0)
		load_max_size_unset_value(history);
	else if (!parse_long(max_str.data, &max))
		load_max_size_invalid_value(history);
	else
	{
		history->adapter.max = (ssize_t)max;
		history_load_max_size_from_logs(max);
	}
	string_free(&max_str);
	return (history->err = error(ERR_NO));
}
