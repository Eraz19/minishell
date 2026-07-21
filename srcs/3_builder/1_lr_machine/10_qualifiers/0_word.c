#include "qualifiers_priv.h"

void	qualify_word(
			const t_token *token,
			bool assignment_disabled,
			t_symbol *out_symbol)
{
	(void)token;
	(void)assignment_disabled;
	*out_symbol = SYM_WORD;
}
