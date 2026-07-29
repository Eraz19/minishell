#include "generator_first.h"
#include "generator_first_priv.h"

static inline void	reset_result(bool *result)
{
	size_t	i;

	i = 0;
	while (i <= SYM_TERMINAL_MAX)
		result[i++] = false;
}

void	first(
			const bool first[SYM_COUNT * (SYM_TERMINAL_MAX + 1)],
			const bool nullable_symbols[SYM_COUNT],
			t_first_param *param)
{
	size_t		pos;
	t_symbol	symbol;
	size_t		offset;

	reset_result(param->result);
	pos = 0;
	while (pos < param->count)
	{
		symbol = param->symbols[pos++];
		if (symbol <= SYM_TERMINAL_MAX)
		{
			param->result[symbol] = true;
			return ;
		}
		offset = symbol * (SYM_TERMINAL_MAX + 1);
		first_add_list(param->result, first + offset, NULL);
		if (nullable_symbols[symbol] == false)
			return ;
	}
	if (param->has_lookahead)
		param->result[param->lookahead] = true;
}
