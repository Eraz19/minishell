#include "params.h"
#include "param_expansion_.h"

static bool	is_valid_param(t_expander_word_item *item)
{
	if (item->c == '?'
		|| item->c == '#'
		|| item->c == '-'
		|| item->c == '*'
		|| item->c == '$'
		|| item->c == '!'
		|| item->c == '@'
		|| item->c == '_'
		|| ft_isalnum(item->c))
		return (true);
	return (false);
}

bool	is_param_expansion(
	t_expander *state,
	t_expander_word *word,
	t_expander_word_item *current_item)
{
	t_expander_word_item	item;

	state->err = expander_word_peek(word, &item, 0);
	if (state->err.type)
		return (false);
	if (current_item->opt.context == CONTEXT_PARAM)
		return (true);
	if (current_item->opt.context != CONTEXT_NONE
		|| current_item->opt.quoted == CONTEXT_SQUOTE
		|| current_item->opt.escaped)
		return (false);
	else if (current_item->c == '$' && is_valid_param(&item))
		return (true);
	return (false);
}

t_error	get_ifs(t_expander *state, t_string	*ifs)
{
	string_init(ifs, 0, NULL, 0);
	state->err = params_get_from_const("IFS", ifs);
	if (state->err.type != ERR_NO && state->err.type != ERR_VAR_NOT_FOUND)
		return (string_free(ifs), state->err);
	if (state->err.type == ERR_VAR_NOT_FOUND)
	{
		state->err = error(ERR_NO);
		if (ifs->data == NULL)
		{
			if (!string_append_n(ifs, "", -1))
				return (state->err = error_sys(), string_free(ifs), state->err);
		}
		else 
			if (!string_append_n(ifs, " \t\n", 3))
				return (state->err = error_sys(), string_free(ifs), state->err);
	}
	return (state->err);
}

t_error	param_expansion_braces(
	t_expander *state,
	t_expander_word *word,
	t_expander_word *word_exp)
{
	
}

t_error	expand_positional_unquoted(
	t_expander *state,
	t_expander_word *word_exp,
	const t_positionals *positional_args)
{
	size_t		i;
	t_string	ifs;
	t_string	param_exp;

	if (get_ifs(state, &ifs).type != ERR_NO)
		return (state->err);
	state->err = params_get_positionals(&positional_args);
	if (state->err.type)
		return (state->err);
	i = 0;
	string_init(&param_exp, 0, NULL, 0);
	while (i < positional_args->len)
	{
		if (!string_append(&param_exp, ))
	}
}

t_error	param_expand_positional(
	t_expander *state,
	t_expander_fields *fields,
	t_expander_word *word,
	t_expander_word *word_exp)
{
	t_expander_word_item	item;	
	const t_positionals		*positional_args;

	state->err = expander_word_pop(word, &item);
	if (state->err.type != ERR_NO)
		return (state->err);
	if (item.opt.quoted == CONTEXT_DQUOTE)
	
	else
		return (expand_positional_unquoted(state, word_exp, positional_args));
}

t_error	param_expand_special(
	t_expander *state,
	t_expander_fields *fields,
	t_expander_word *word,
	t_expander_word *word_exp)
{
	t_expander_word_item	item;

	state->err = expander_word_remove(word, 0, 1);
	if (state->err.type)
		return (state->err);
	state->err = expander_word_peek(word, &item, 0);
	if (state->err.type)
		return (state->err);
	if (item.c == '@' || item.c == '*')
		return (param_expand_positional(state, fields, word, word_exp));
	else if ()
}

t_error	param_expansion(
	t_expander *state,
	t_expander_fields *fields,
	t_expander_word *word,
	t_expander_word *word_exp)
{
	t_expander_word_item	item;

	state->err = expander_word_peek(word, &item, 0);
	if (state->err.type)
		return (state->err);
	if (item.opt.context == CONTEXT_PARAM)
		return (param_expansion_braces(state, word, word_exp));
	else
		return (param_expansion_special(state, word, word_exp));
}
