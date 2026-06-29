#include "utils.h"
#include "params.h"
#include "tilde_expansion_.h"

bool	is_tilde_expansion(
	t_expander *state,
	t_expander_word *word,
	t_expander_word_item *current_item)
{
	t_expander_word_item	item;

	state->err = expander_word_peek(word, &item, 0);
	if (state->err.type)
		return (false);
	if (item.opt.quoted != CONTEXT_NONE || current_item->opt.escaped)
		return (false);
	if (current_item->opt.i == 0 && current_item->c == '~')
		return (true);
	else if (state->assignement_offset > 0
		&& item.opt.i == (size_t)state->assignement_offset + 1
		&& current_item->c == '='
		&& item.c == '~')
		return (true);
	else if (state->role == EXPANDER_ASSIGNMENT
		&& state->assignement_offset > 0
		&& current_item->opt.i > (size_t)state->assignement_offset
		&& current_item->c == ':'
		&& item.c == '~')
		return (true);
	return (false);
}

static t_error	tilde_extract_username(t_expander *state, char **username)
{
	size_t					i;
	t_expander_word_item	item;

	i = 0;
	while (i + 1 < state->word.len)
	{
		state->err = expander_word_get(&state->word, i + 1, &item);
		if (state->err.type)
			return (state->err);
		if (item.c == '/')
			break ;
		else if (state->role == EXPANDER_ASSIGNMENT && item.c == ':')
			break ;
		else if (item.opt.quoted != CONTEXT_NONE)
			return (*username = NULL, state->err);
		i++;
	}
	return (state->err = expander_word_to_str(&state->word, username, 1, i));
}

static t_error	tilde_resolve_path(
					t_expander *state,
					char **path,
					char *username)
{
	struct passwd	*password;
	t_string		home;

	*path = NULL;
	if (username[0] == '\0')
	{
		state->err = params_get_from_const("HOME", &home);
		if (state->err.type)
			return (state->err);
		*path = home.data;
		return (state->err);
	}
	else
	{
		state->err = ft_getpwnam(username, &password);
		if (state->err.type)
			return (state->err);
		if (password)
			*path = password->pw_dir;
		return (state->err);
	}
}

t_error	tilde_expansion(
	t_expander *state,
	t_expander_word *word,
	t_expander_word *word_exp)
{
	t_expander_word_item_opt	opt;
	t_expander_word_item		item;
	char						*path;
	char						*username;

	if (tilde_extract_username(state, &username).type || username == NULL)
		return (state->err);
	if (tilde_resolve_path(state, &path, username).type || path == NULL)
		return (state->err);
	state->err = expander_word_pop(word, &item);
	if (state->err.type)
		return (state->err);
	opt = (t_expander_word_item_opt){
		.is_expand_res = false,
		.quoted = item.opt.quoted,
		.context = item.opt.context,
	};
	state->err = expander_word_from_str(word_exp, path, opt);
	if (state->err.type)
		return (state->err);
	state->err = expander_word_remove(&state->word, 0, str_len(path));
	return (state->err);
}
