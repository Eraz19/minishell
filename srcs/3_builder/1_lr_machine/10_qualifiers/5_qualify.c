#include "qualifiers_priv.h"
# include <assert.h>	// DEBUG

void	qualify_5(
			const t_token *token,
			bool assignment_disabled,
			t_symbol *out_symbol)
{
	assert(out_symbol != NULL);
	assert(token != NULL);
	(void)assignment_disabled;
	if (!qualify_try_name(token, out_symbol))
		*out_symbol = SYM_WORD;
}
