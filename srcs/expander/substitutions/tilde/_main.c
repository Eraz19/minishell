#include "error.h"
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
