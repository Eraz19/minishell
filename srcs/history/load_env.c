/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 16:25:29 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/20 11:49:17 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "params.h"
#include "history.h"

t_error	history_load_path_env(t_history *state)
{
	char	*path;

	state->err = params_get("HISTFILE", &state->file.path);
	if (state->err.type && state->err.type != ERR_VAR_NOT_FOUND)
		return (state->err);
	if (state->err.type == ERR_VAR_NOT_FOUND || state->file.path == NULL)
	{
		state->err = params_get("HOME", &path);
		if (state->err.type && state->err.type != ERR_VAR_NOT_FOUND)
			return (state->err);
		state->file.path = str_join(path, "/.sh_history");
		if (state->file.path == NULL)
			return (free(path), state->err = error_sys());
		free(path);
	}
	state->err = error(ERR_NO);	// TO_CHECK
	return (state->err);
}

t_error	history_load_size_env(t_history *state)
{
	ssize_t	max;
	char	*max_str;
	
	state->err = params_get("HISTSIZE", &max_str);
	if (state->err.type && state->err.type != ERR_VAR_NOT_FOUND)
		return (state->err);
	if (state->err.type == ERR_VAR_NOT_FOUND || max_str == NULL)
		state->rl_history.max = -1;
	else
	{
		max = (ssize_t)ft_atol(max_str);
		state->rl_history.max = max;
		if (max >= 0 && max < 128)
			state->rl_history.max = 128;
	}
	state->err = error(ERR_NO);	// TO_CHECK
	return (state->err);
}
