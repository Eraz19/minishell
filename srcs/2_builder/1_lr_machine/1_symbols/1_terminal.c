#include "symbols.h"

bool	symbol_is_terminal(t_symbol symbol)
{
	return (symbol >= SYM_TERMINAL_MIN && symbol <= SYM_TERMINAL_MAX);
}

bool	symbol_is_non_terminal(t_symbol symbol)
{
	return (symbol >= SYM_NON_TERMINAL_MIN && symbol <= SYM_NON_TERMINAL_MAX);
}
