/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:44:52 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/06 00:34:22 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_.h"

t_error	word_match_pattern(
			bool *match,
			const t_word *pattern,
			const char *str,
			size_t len)
{
	t_error		err;
	t_string	rendered;

	*match = false;
	err = pattern_from_word(&rendered, pattern, true);
	if (err.type)
		return (requalify_expander_error(err));
	*match = match_pattern(rendered.data, str, len);
	return (string_free(&rendered), error(ERR_NO));
}
