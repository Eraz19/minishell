#include "cmd_expansion.h"

void	cmd_expansions_init(t_cmd_expansions *expansions)
{
	(void)vector_init(expansions, sizeof(t_expansion), 0);
}

void	cmd_expansions_free(t_cmd_expansions *expansions)
{
	vector_free(expansions, expansion_free_void);
}
