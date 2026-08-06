/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:48:03 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/05 23:26:00 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "env.h"
#include "expander_.h"
#include "tilde_expansion_.h"

t_error	keep_tilde_prefix_literal(t_expander *expander, t_string *username)
{
	size_t	len;

	len = username->len;
	expander->err = forward_word_item(&expander->word_exp, &expander->word);
	if (expander->err.type)
		return (expander->err);
	while (len > 0)
	{
		expander->err = forward_word_item(&expander->word_exp, &expander->word);
		if (expander->err.type)
			return (expander->err);
		len--;
	}
	return (expander->err);
}

t_error	extract_username(t_expander *expander, t_string *out)
{
	size_t		i;
	t_word_item	item;

	i = 0;
	while (i + 1 < expander->word.len)
	{
		word_get(&item, &expander->word, i + 1);
		if (item.opt.quoted != CONTEXT_NONE)
			return (expander->err = error(ERR_QUOTED_TILDE));
		if (item.c == '/')
			break ;
		if (expander->assignment_offset > 0 && item.c == ':')
			break ;
		i++;
	}
	if (i == 0)
		return (expander->err = error(ERR_NO));
	return (expander->err = to_str(out, &expander->word, 1, i));
}

t_error	resolve_path(
			t_expander *expander,
			t_string *out,
			t_string *username,
			bool *ok)
{
	t_string		home;
	const char		*out_str;
	struct passwd	*password;

	*ok = false;
	if (username->len != 0)
	{
		expander->err = ft_getpwnam(username->data, &password);
		if (expander->err.type || password == NULL)
			return (expander->err);
		if (!string_init(out, 0, password->pw_dir, -1))
			return (expander->err = error_sys());
		return (*ok = true, expander->err);
	}
	expander->err = env_get_from_const("HOME", &home);
	if (expander->err.type == ERR_VAR_NOT_FOUND)
		return (expander->err = error(ERR_NO));
	if (expander->err.type)
		return (expander->err);
	out_str = "";
	if (home.data)
		out_str = home.data;
	if (!string_init(out, 0, out_str, -1))
		return (string_free(&home), expander->err = error_sys());
	return (*ok = true, string_free(&home), expander->err);
}

t_error	replace_with_path(
			t_expander *expander,
			t_string *path,
			t_string *username)
{
	t_word_item_opt	opt;
	t_word_item		item;
	t_word			path_word;

	word_fpop(&item, &expander->word);
	opt = item.opt;
	opt.quoted = CONTEXT_DQUOTE;
	opt.is_expand_res = true;
	expander->err = from_str(&path_word, path, opt);
	if (expander->err.type)
		return (expander->err);
	while (path_word.len > 0)
	{
		expander->err = forward_word_item(&expander->word_exp, &path_word);
		if (expander->err.type)
			return (word_free(&path_word), expander->err);
	}
	word_free(&path_word);
	expander->err = word_remove(&expander->word, 0, username->len);
	return (expander->err);
}

t_error	expand_user_path(t_expander *expander)
{
	bool		ok;
	t_string	path;
	t_string	username;

	string_init(&username, 0, NULL, 0);
	extract_username(expander, &username);
	if (expander->err.type != ERR_NO && expander->err.type != ERR_QUOTED_TILDE)
		return (string_free(&username), expander->err);
	if (expander->err.type != ERR_NO)
	{
		expander->err = error(ERR_NO);
		keep_tilde_prefix_literal(expander, &username);
		return (string_free(&username), expander->err);
	}
	if (resolve_path(expander, &path, &username, &ok).type)
		return (string_free(&username), expander->err);
	if (!ok)
	{
		keep_tilde_prefix_literal(expander, &username);
		return (string_free(&username), expander->err);
	}
	if (replace_with_path(expander, &path, &username).type)
		return (string_free(&path), string_free(&username), expander->err);
	return (string_free(&path), string_free(&username), expander->err);
}
