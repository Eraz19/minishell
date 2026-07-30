#include "grammar_qualifiers.h"
#include "grammar_qualifiers_priv.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG

void	qualify_5(
			char *token_value,
			ssize_t assignment_offset,
			t_symbol *out_symbol)
{
	assert(token_value != NULL);
	assert(out_symbol != NULL);
	if (!qualify_try_name(token_value, assignment_offset, out_symbol))
		*out_symbol = SYM_WORD;
}
