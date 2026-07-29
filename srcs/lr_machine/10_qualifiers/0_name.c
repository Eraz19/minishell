#include "qualifiers_priv.h"
#include "utils.h"
# include <assert.h>	// DEBUG

bool	qualify_try_name(const t_token *token, t_symbol *dst_symbol)
{
	assert(token != NULL);
	assert(dst_symbol != NULL);
	if (!name_is_valid_str(&token->value))
		return (false);
	*dst_symbol = SYM_NAME;
	return (true);
}
