#include "grammar_qualifiers.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG

void	qualify_2(
			char *token_value,
			ssize_t assignment_offset,
			t_symbol *out_symbol)
{
	assert(token_value != NULL);
	assert(out_symbol != NULL);
	(void)token_value;
	(void)assignment_offset;
	*out_symbol = SYM_WORD;
}
