#include "qualifiers_priv.h"
#include "utils.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG
# include <stdio.h>		// DEBUG

void	qualify_7b(const t_token *token, t_symbol *out_symbol)
{
	t_string	truncated;

	assert(out_symbol != NULL);
	assert(token != NULL);
	truncated.data = token->value.data;
	truncated.cap = 0;
	truncated.len = (size_t)token->assignment_offset;
	if (token->assignment_offset != -1 && name_is_valid_str(&truncated))
		*out_symbol = SYM_ASSIGNMENT_WORD;
	else
		*out_symbol = SYM_WORD;
}
