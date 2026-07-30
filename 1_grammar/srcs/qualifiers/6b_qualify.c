#include "grammar_qualifiers.h"
#include "libft.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG

void	qualify_6b(
			char *token_value,
			ssize_t assignment_offset,
			t_symbol *out_symbol)
{
	assert(token_value != NULL);
	assert(out_symbol != NULL);
	(void)assignment_offset;
	if (str_cmp("in", token_value) == 0)
		*out_symbol = SYM_In;
	else if (str_cmp("do", token_value) == 0)
		*out_symbol = SYM_Do;
	else
		*out_symbol = SYM_WORD;
}
