#include "arith_substitution_.h"

bool	is_arith_substitution(t_word_item *current_item, uint flags)
{
	if (!flag_is_active(flags, EXP_ARITH))
		return (false);
	if (current_item->opt.context == CONTEXT_ARITH)
		return (true);
	return (false);
}

t_error	arith_substitution(t_expander *expander)
{
	(void)expander;
	return (expander->err);
}
