#include "qualifiers_priv.h"
# include <assert.h>	// DEBUG

void	qualify_6b(const t_token *token, t_symbol *out_symbol)
{
	assert(out_symbol != NULL);
	assert(token != NULL);
	if (str_cmp("in", token->value.data) == 0)
		*out_symbol = SYM_In;
	else if (str_cmp("do", token->value.data) == 0)
		*out_symbol = SYM_Do;
	else
		*out_symbol = SYM_WORD;
}
