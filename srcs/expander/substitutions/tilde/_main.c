#include "error.h"
#include "expander.h"
#include "tilde_expansion_.h"

bool	is_tilde_flag_set(t_expander *expander, t_exp_flag *tilde_flag)
{
	if (flag_is_active((uint)expander->flags, EXP_TILDE_NORMAL))
		return (*tilde_flag = EXP_TILDE_NORMAL, true);
	else if (flag_is_active((uint)expander->flags, EXP_TILDE_ASSIGNMENT))
		return (*tilde_flag = EXP_TILDE_ASSIGNMENT, true);
	else
		return (false);
}

bool	is_tilde_expansion(t_expander *expander, t_word_item *current_item)
{
	t_word_item	item;
	bool		escaped;
	t_exp_flag	tilde_flag;
	size_t		assign_offset;

	if (!is_tilde_flag_set(expander, &tilde_flag))
		return (false);
	escaped = current_item->opt.escaped;
	if (current_item->opt.i == 0 && current_item->c == '~')
		return (current_item->opt.quoted == CONTEXT_NONE && !escaped);
	if (tilde_flag == EXP_TILDE_NORMAL)
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

t_error	tilde_consume_assign_char(t_expander *expander)
{
	t_word_item		item;

	expander->err = word_get(&item, &expander->word, 0);
	if (expander->err.type)
		return (expander->err);
	if (item.c == '=' || item.c == ':')
	{
		expander->err = forward_word_item(&expander->word_exp, &expander->word);
		if (expander->err.type)
			return (expander->err);
	}
	return (expander->err);
}

t_error	tilde_expansion(t_expander *expander)
{
	if (tilde_consume_assign_char(expander).type)
		return (expander->err);
	if (expand_user_path(expander).type)
		return (expander->err);
	return (expander->err);
}
