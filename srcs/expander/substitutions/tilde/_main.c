#include "error.h"
#include "utils.h"
#include "params.h"
#include "tilde_expansion_.h"

bool	is_tilde_expansion(t_expander *expander, t_word_item *current_item)
{
	t_word_item	item;
	bool		escaped;
	size_t		assign_offset;

	if (!flag_is_active((uint)expander->flags, EXP_TILDE))
		return (false);
	escaped = current_item->opt.escaped;
	if (current_item->opt.i == 0 && current_item->c == '~')
		return (current_item->opt.quoted == CONTEXT_NONE && !escaped);
	if (expander->assignment_offset <= 0)
		return (false);
	expander->err = word_get(&item, &expander->word, 1);
	if (expander->err.type)
		return (false);
	if (item.c != '~' || item.opt.escaped)
		return (false);
	if (item.opt.quoted != CONTEXT_NONE)
		return (false);
	assign_offset = (size_t)expander->assignment_offset;
	if (item.opt.i == assign_offset + 1 && current_item->c == '=')
		return (true);
	return (current_item->opt.i > assign_offset && current_item->c == ':');
}

t_error	extract_username(t_expander *expander, t_string *out)
{
	size_t		i;
	t_word_item	item;

	i = 0;
	while (i + 1 < expander->word.len)
	{
		expander->err = word_get(&item, &expander->word, i + 1);
		if (expander->err.type)
			return (expander->err);
		if (item.c == '/')
			break ;
		else if (expander->assignment_offset > 0 && item.c == ':')
			break ;
		else if (item.opt.quoted != CONTEXT_NONE)
			return (expander->err = error(ERR_QUOTED_TILDE));
		i++;
	}
	return (expander->err = to_str(out, &expander->word, 1, i));
}

t_error	resolve_path(t_expander *expander, t_string *out, t_string *username)
{
	t_string		home;
	struct passwd	*password;

	if (username->len == 0)
	{
		expander->err = params_get_from_const("HOME", &home);
		if (expander->err.type)
			return (expander->err);
		if (!string_init(out, 0, home.data, -1))
			expander->err = error_sys();
		return (string_free(&home), expander->err);
	}
	else
	{
		expander->err = ft_getpwnam(username->data, &password);
		if (expander->err.type)
			return (expander->err);
		if (password != NULL && !string_init(out, 0, password->pw_dir, -1))
			expander->err = error_sys();
		return (expander->err);
	}
}

t_error	tilde_consume_assign_char(t_expander *expander)
{
	t_word_item		item;

	expander->err = word_get(&item, &expander->word, 1);
	if (expander->err.type)
		return (expander->err);
	if (item.c == '=' || item.c == ':')
	{
		expander->err = word_push(&expander->word_exp, item);
		if (expander->err.type)
			return (expander->err);
		expander->err = word_remove(&expander->word, 0, 1);
		if (expander->err.type)
			return (expander->err);
	}
	return (expander->err);
}

t_error	tilde_expansion(t_expander *expander)
{
	t_word_item_opt	opt;
	t_word_item		item;
	t_string		path;
	t_string		username;

	if (tilde_consume_assign_char(expander).type)
		return (expander->err);
	string_init(&username, 0, NULL, 0);
	extract_username(expander, &username);
	if (expander->err.type != ERR_NO && expander->err.type != ERR_QUOTED_TILDE)
		return (string_free(&username), expander->err);
	expander->err = error(ERR_NO);
	if (resolve_path(expander, &path, &username).type || path.len == 0)
		return (string_free(&username), string_free(&path), expander->err);
	expander->err = word_fpop(&item, &expander->word);
	if (expander->err.type)
		return (string_free(&username), string_free(&path), expander->err);
	opt = item.opt;
	opt.is_expand_res = false;
	expander->err = from_str(&expander->word_exp, &path, opt);
	if (expander->err.type)
		return (string_free(&username), string_free(&path), expander->err);
	expander->err = word_remove(&expander->word, 0, username.len);
	return (string_free(&username), string_free(&path), expander->err);
}
