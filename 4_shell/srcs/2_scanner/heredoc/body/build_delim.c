/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_delim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:11:24 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:11:25 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_error	build_heredoc_delimiter(t_string *out, t_token *delim)
{
	t_error	err;
	int		exit_status;

	exit_status = -1;
	err = expand_token_merged(out, delim, &exit_status, EXP_QUOTE_REMOVAL);
	if (err.type)
		return (err);
	if (!string_append_n(out, "\n", 1))
		return (err = error_sys(), string_free(out), err);
	return (error(ERR_NO));
}
