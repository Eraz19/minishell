#include "grammar_qualifiers.h"
#include "grammar_name.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG
# include <stdio.h>		// DEBUG

void	qualify_7b(
			char *token_value,
			ssize_t assignment_offset,
			t_symbol *out_symbol)
{
	char	c;

	assert(token_value != NULL);
	assert(out_symbol != NULL);
	if (assignment_offset < 0)
	{
		*out_symbol = SYM_WORD;
		return ;
	}
	c = token_value[assignment_offset];
	token_value[assignment_offset] = '\0';
	if (name_is_valid(token_value))
		*out_symbol = SYM_ASSIGNMENT_WORD;
	else
		*out_symbol = SYM_WORD;
	token_value[assignment_offset] = c;
}
