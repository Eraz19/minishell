#include "generator_goto.h"
#include <stdlib.h>

void	goto_init(size_t **gotos)
{
	*gotos = NULL;
}

void	goto_free(size_t **gotos)
{
	if (!gotos || !*gotos)
		return ;
	free(*gotos);
	*gotos = NULL;
}
