#include "resolve_priv.h"

bool	cmd_resolve_is_declaration_utility(const char *name)
{
	return (str_cmp(name, "export") == 0 || str_cmp(name, "readonly") == 0);
}
