/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:44:52 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:44:56 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "expander_.h"

static bool	pattern_char_active(t_word_item item)
{
	if (item.opt.escaped)
		return (false);
	if (is_context_quoting(item.opt.local_quoted)
		|| item.opt.local_quoted == CONTEXT_HEREDOC)
		return (false);
	return (true);
}

static bool	pattern_push_item(t_string *out, t_word_item item)
{
	char	c;
	char	backslash;

	c = item.c;
	backslash = '\\';
	if (pattern_char_active(item) && (c == '*' || c == '?' || c == '['))
		return (string_append_n(out, &c, 1));
	if (c == '*' || c == '?' || c == '[' || c == '\\')
		if (!string_append_n(out, &backslash, 1))
			return (false);
	return (string_append_n(out, &c, 1));
}

t_error	pattern_from_word(t_string *out, const t_word *pattern)
{
	size_t		i;
	t_error		err;
	t_word_item	item;

	if (!string_init(out, 0, "", -1))
		return (error_sys());
	i = 0;
	while (i < pattern->len)
	{
		err = word_get(&item, pattern, i++);
		if (err.type)
			return (string_free(out), err);
		if (!pattern_push_item(out, item))
			return (string_free(out), error_sys());
	}
	return (error(ERR_NO));
}

t_error	word_match_pattern(
			bool *match,
			const t_word *pattern,
			const char *str,
			size_t len)
{
	t_error		err;
	t_string	rendered;

	*match = false;
	err = pattern_from_word(&rendered, pattern);
	if (err.type)
		return (expander_error_qualify(err));
	*match = match_pattern(rendered.data, str, len);
	return (string_free(&rendered), error(ERR_NO));
}
