#include "symbols_type.h"
#include <stdbool.h>

bool	symbol_is_reserved_word(t_symbol symbol)
{
	return (symbol >= SYM_RESERVED_MIN && symbol <= SYM_RESERVED_MAX);
}
