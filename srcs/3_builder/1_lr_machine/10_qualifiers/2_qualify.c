#include "qualifiers_priv.h"
# include <assert.h>	// DEBUG

void	qualify_2(
			const t_token *token,
			bool assignment_disabled,
			t_symbol *out_symbol)
{
	assert(out_symbol != NULL);
	(void)token;
	(void)assignment_disabled;
	/*
	TODO:
		"The expansions specified in 2.7 Redirection shall occur.
		As specified there, exactly one field can result (or the result is unspecified).
		And there are additional requirements on pathname expansion.""	
	*/
	*out_symbol = SYM_WORD;
}
