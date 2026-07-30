#include "qualifiers_priv.h"
# include <assert.h>	// DEBUG

void	qualify_7a(const t_token *token, t_symbol *out_symbol)
{
	assert(out_symbol != NULL);
	assert(token != NULL);
	if (qualify_try_reserved_word(token, out_symbol))
		return ;
	qualify_7b(token, out_symbol);
}
