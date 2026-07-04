#include "cmd_substitution_.h"

bool	is_cmd_substitution(t_word_item *current_item, uint flags)
{
	if (!flag_is_active((uint)flags, EXP_CMD_SUB))
		return (false);
	if (current_item->opt.context == CONTEXT_CMD_SUB)
		return (true);
	return (false);
}

t_error	cmd_substitution(t_expander *expander)
{
	(void)expander;
	return (expander->err);
}
