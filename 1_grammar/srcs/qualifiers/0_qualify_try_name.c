#include "grammar_qualifiers_priv.h"
#include "grammar_name.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG

bool	qualify_try_name(
			char *token_value,
			ssize_t assignment_offset,
			t_symbol *out_symbol)
{
	assert(token_value != NULL);
	assert(out_symbol != NULL);
	(void)assignment_offset;
	if (!name_is_valid(token_value))
		return (false);
	*out_symbol = SYM_NAME;
	return (true);
}
