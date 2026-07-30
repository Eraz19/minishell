#include "qualifiers_priv.h"

void	qualify_word(const t_token *token, t_symbol *out_symbol)
{
	(void)token;
	*out_symbol = SYM_WORD;
}
