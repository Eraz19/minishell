#include "builder.h"
#include <stdbool.h>

void	add_first(bool *dst, bool *did_add)
{
	if (did_add && *dst == false)
		*did_add = true;
	*dst = true;
}

void	add_first_list(bool *dst, bool *src, bool *did_add)
{
	t_symbol	terminal;

	terminal = 0;
	while (terminal <= SYM_TERMINAL_MAX)
	{
		if (src[terminal] == true)
			add_first(&dst[terminal], did_add);
		terminal++;
	}
}
