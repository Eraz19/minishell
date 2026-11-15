/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_helpers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:09:30 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 21:34:42 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdlib.h>

t_error	option_is_active(t_option option, bool *out)
{
	t_params	*params;
	t_error		err;

	params = shell_get_params();
	if (!params)
	{
		err = error_print(error(ERR_SHELL_NOT_FOUND), __func__, NULL, NULL);
		err.type = ERR_INTERNAL;
		return (err);
	}
	*out = (params->options & option) != 0;
	return (error(ERR_NO));
}

bool	option_is_active_in(t_option options, t_option option)
{
	return ((options & option) != 0);
}

void	option_set(t_option *options, t_option option, bool on)
{
	if (on)
		*options |= option;
	else
		*options &= ~option;
}

static void	options_add_to_string(t_option options, char *buff, size_t *len)
{
	if (option_is_active_in(options, OPT_NOCLOBBER))
		buff[(*len)++] = 'C';
	if (option_is_active_in(options, OPT_ERREXIT))
		buff[(*len)++] = 'e';
	if (option_is_active_in(options, OPT_NOGLOB))
		buff[(*len)++] = 'f';
	if (option_is_active_in(options, OPT_CMD_HASH))
		buff[(*len)++] = 'h';
	if (option_is_active_in(options, OPT_INTERACTIVE))
		buff[(*len)++] = 'i';
	if (option_is_active_in(options, OPT_MONITOR))
		buff[(*len)++] = 'm';
	if (option_is_active_in(options, OPT_NOEXEC))
		buff[(*len)++] = 'n';
	if (option_is_active_in(options, OPT_NOUNSET))
		buff[(*len)++] = 'u';
	if (option_is_active_in(options, OPT_VERBOSE))
		buff[(*len)++] = 'v';
	if (option_is_active_in(options, OPT_XTRACE))
		buff[(*len)++] = 'x';
	if (option_is_active_in(options, OPT_CMD_STRING))
		buff[(*len)++] = 'c';
	if (option_is_active_in(options, OPT_STDIN_INPUT))
		buff[(*len)++] = 's';
}

t_error	options_get(t_option options, t_string *dst)
{
	char	*buff;
	size_t	cap;
	size_t	len;

	cap = OPT_SINGLE_COUNT + 1;
	buff = malloc (cap);
	if (!buff)
		return (error_sys());
	len = 0;
	if (option_is_active_in(options, OPT_EXPORT_ALL))
		buff[len++] = 'a';
	if (option_is_active_in(options, OPT_NOTIFY))
		buff[len++] = 'b';
	options_add_to_string(options, buff, &len);
	buff[len] = '\0';
	string_take(dst, buff, cap, (ssize_t)len);
	return (error(ERR_NO));
}
