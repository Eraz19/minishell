#include "first.h"
#include "first_priv.h"
#include "symbols.h"

static inline void	reset_result(bool *result)
{
	size_t	i;

	i = 0;
	while (i <= SYM_TERMINAL_MAX)
		result[i++] = false;
}

void	first(t_lr_machine *machine, t_first_param *param)
{
	size_t		pos;
	t_symbol	symbol;

	reset_result(param->result);
	pos = 0;
	while (pos < param->count)
	{
		symbol = param->symbols[pos++];
		if (symbol_is_terminal(symbol))
		{
			param->result[symbol] = true;
			return ;
		}
		add_first_list(
			param->result,
			machine->first[symbol],
			NULL);
		if (!symbol_is_nullable(machine, symbol))
			return ;
	}
	if (param->has_lookahead)
		param->result[param->lookahead] = true;
}
