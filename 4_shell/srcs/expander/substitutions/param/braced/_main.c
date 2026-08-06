/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:47:01 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/06 12:24:05 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h> // DEBUG
#include "param_braced_.h"

static t_error	braced_origin(
					t_expander *expander,
					size_t *body_len,
					t_word_item_opt *origin)
{
	t_word_item	item;

	word_get(&item, &expander->word, 0);
	assert(item.opt.context_len >= 3);
	*body_len = item.opt.context_len - 3;
	*origin = item.opt;
	return (expander->err);
}

t_error	expand_braced_dispatch(
			t_expander *expander,
			size_t body_len,
			t_word_item_opt origin)
{
	t_word_item	item;

	word_get(&item, &expander->word, 0);
	if (item.c == '#')
		return (expand_braced_length(expander, body_len, origin));
	if (item.c == '@' || item.c == '*')
		return (expand_braced_positional(expander, body_len, origin));
	return (expand_braced_param(expander, body_len, origin));
}

t_error	requalify_error(t_expander *expander, t_string body)
{
	expander->err = error_print(expander->err,
			"expander", body.data, NULL, NULL);
	expander->err.type = ERR_POSIX_EXPANSION;
	return (expander->err);
}

t_error	expand_braced(t_expander *expander)
{
	t_string		body;
	t_word_item_opt	origin;
	size_t			body_len;

	expander->err = braced_origin(expander, &body_len, &origin);
	if (expander->err.type)
		return (expander->err);
	expander->err = to_str(&body, &expander->word, 0, body_len + 3);
	if (expander->err.type)
		return (expander->err);
	expander->err = word_remove(&expander->word, 0, 2);
	if (expander->err.type)
		return (string_free(&body), expander->err);
	if (body_len == 0)
	{
		expander->err = error(ERR_PARAM_BAD_SUBSTITUTION);
		return (requalify_error(expander, body), string_free(&body),
			expander->err);
	}
	expander->err = expand_braced_dispatch(expander, body_len, origin);
	if (expander->err.type == ERR_PARAM_BAD_SUBSTITUTION
		|| expander->err.type == ERR_VAR_INVALID_NAME)
		requalify_error(expander, body);
	return (string_free(&body), expander->err);
}
