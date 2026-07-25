#include "qualifiers_priv.h"
# include <assert.h>	// DEBUG

void	qualify_6a(const t_token *token, t_symbol *out_symbol)
{
	assert(out_symbol != NULL);
	assert(token != NULL);
	if (str_cmp("in", token->value.data) == 0)
		*out_symbol = SYM_In;
	else
		*out_symbol = SYM_WORD;
}
