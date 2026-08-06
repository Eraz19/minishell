/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 00:32:24 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/06 00:34:26 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_.h"

static bool	pattern_char_active(t_word_item item, bool res_quoted)
{
	if (item.opt.escaped)
		return (false);
	if (res_quoted && item.opt.is_expand_res)
		return (!is_context_quoting(item.opt.quoted)
			&& item.opt.quoted != CONTEXT_HEREDOC);
	if (is_context_quoting(item.opt.local_quoted)
		|| item.opt.local_quoted == CONTEXT_HEREDOC)
		return (false);
	return (true);
}

static bool	is_pattern_meta(char c)
{
	return (c == '*' || c == '?' || c == '[' || c == ']'
		|| c == '!' || c == '^' || c == '-' || c == '\\');
}

static bool	pattern_push_literal(t_string *out, char c)
{
	char	backslash;

	backslash = '\\';
	if (is_pattern_meta(c))
		if (!string_append_n(out, &backslash, 1))
			return (false);
	return (string_append_n(out, &c, 1));
}

static bool	pattern_push_item(t_string *out, t_word_item item, bool res_quoted)
{
	if (pattern_char_active(item, res_quoted) && item.c != '\\')
		return (string_append_n(out, &item.c, 1));
	return (pattern_push_literal(out, item.c));
}

t_error	pattern_from_word(t_string *out, const t_word *pattern, bool res_quoted)
{
	size_t		i;
	t_word_item	item;
	t_word_item	next;

	if (!string_init(out, 0, "", -1))
		return (error_sys());
	i = 0;
	while (i < pattern->len)
	{
		word_get(&item, pattern, i++);
		if (item.c == '\\' && pattern_char_active(item, res_quoted)
			&& i < pattern->len)
		{
			word_get(&next, pattern, i);
			i++;
			if (!pattern_push_literal(out, next.c))
				return (string_free(out), error_sys());
			continue ;
		}
		if (!pattern_push_item(out, item, res_quoted))
			return (string_free(out), error_sys());
	}
	return (error(ERR_NO));
}
