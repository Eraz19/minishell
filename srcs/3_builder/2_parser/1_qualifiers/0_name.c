#include "symbols_type.h"
#include "utils.h"

bool	qualify_try_name(const char *token_value, t_symbol *dst_symbol)
{
	if (!name_is_valid(token_value))
		return (false);
	*dst_symbol = SYM_NAME;
	return (true);
}
