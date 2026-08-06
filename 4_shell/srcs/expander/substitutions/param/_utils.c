/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:47:50 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/05 23:23:11 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "options.h"
#include "expander_.h"

t_error	param_nounset_error(t_expander *expander, const char *name)
{
	bool	nounset;

	if (name[0] != '\0' && name[1] == '\0'
		&& (name[0] == '@' || name[0] == '*'))
		return (expander->err = error(ERR_NO));
	expander->err = option_is_active(OPT_NOUNSET, &nounset);
	if (expander->err.type || !nounset)
		return (expander->err);
	expander->err = error_print(error(ERR_PARAM_NULL_OR_UNSET),
			name, "parameter not set", NULL, NULL);
	expander->err.type = ERR_POSIX_EXPANSION;
	return (expander->err);
}

size_t	scan_param_run(t_expander *expander, size_t i, bool digits)
{
	t_word_item	item;

	while (i < expander->word.len)
	{
		word_get(&item, &expander->word, i);
		if (digits && !ft_isdigit(item.c))
			break ;
		if (!digits && item.c != '_' && !ft_isalnum(item.c))
			break ;
		i++;
	}
	return (i);
}

t_error	get_param_name(t_expander *expander, t_string *param_name, bool braced)
{
	size_t		i;
	t_word_item	item;

	word_get(&item, &expander->word, 0);
	i = 1;
	if (ft_isalpha(item.c) || item.c == '_')
		i = scan_param_run(expander, 1, false);
	else if (braced && ft_isdigit(item.c))
		i = scan_param_run(expander, 1, true);
	expander->err = to_str(param_name, &expander->word, 0, i);
	if (expander->err.type)
		return (expander->err);
	return (expander->err = word_remove(&expander->word, 0, i));
}

t_error	drop_quoted_null_at(t_expander *expander)
{
	t_word_item	open;
	t_word_item	close;

	if (expander->word_exp.len == 0 || expander->word.len < 2)
		return (expander->err);
	word_get(&open, &expander->word_exp, expander->word_exp.len - 1);
	word_get(&close, &expander->word, 1);
	if (open.c != '"' || open.opt.is_expand_res || open.opt.escaped
		|| close.c != '"' || close.opt.is_expand_res || close.opt.escaped)
		return (expander->err);
	expander->err = word_remove(&expander->word_exp,
			expander->word_exp.len - 1, 1);
	if (expander->err.type)
		return (expander->err);
	return (expander->err = word_remove(&expander->word, 1, 1));
}

t_word_item	simple_dquote_item(t_word_item_opt opt)
{
	t_word_item	item;

	item.c = '"';
	item.opt = opt;
	item.opt.is_expand_res = false;
	return (item);
}
