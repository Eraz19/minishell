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

t_error	param_expansion(
	t_expander *state,
	t_expander_word *word,
	t_expander_word *word_exp)
{
	(void)state;
	(void)word;
	(void)word_exp;
	return (state->err);
}
