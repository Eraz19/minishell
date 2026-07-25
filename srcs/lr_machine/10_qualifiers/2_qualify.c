#include "qualifiers_priv.h"
# include <assert.h>	// DEBUG

void	qualify_2(const t_token *token, t_symbol *out_symbol)
{
	assert(out_symbol != NULL);
	(void)token;
	*out_symbol = SYM_WORD;
}
