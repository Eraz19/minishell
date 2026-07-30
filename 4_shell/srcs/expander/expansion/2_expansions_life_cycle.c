#include "expander.h"

void	cmd_expansions_init(t_expansions *expansions)
{
	(void)vector_init(expansions, sizeof(t_expansion), 0);
}

void	cmd_expansions_free(t_expansions *expansions)
{
	vector_free(expansions, expansion_free_void);
}
