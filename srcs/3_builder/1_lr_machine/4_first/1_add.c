#include "builder.h"
#include <stdbool.h>

void	first_add(bool *dst, bool *did_add)
{
	if (did_add && *dst == false)
		*did_add = true;
	*dst = true;
}

void	first_add_list(bool *dst, const bool *src, bool *did_add)
{
	t_symbol	terminal;

	terminal = 0;
	while (terminal <= SYM_TERMINAL_MAX)
	{
		if (src[terminal] == true)
			first_add(&dst[terminal], did_add);
		terminal++;
	}
}
