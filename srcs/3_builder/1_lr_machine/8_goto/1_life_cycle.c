#include <stdlib.h>

void	goto_init(size_t ***gotos)
{
	*gotos = NULL;
}

void	goto_free(size_t lr_states_count, size_t ***gotos)
{
	size_t	i;

	if (!gotos || !*gotos)
		return ;
	i = 0;
	while (i < lr_states_count)
	{
		free((*gotos)[i]);
		i++;
	}
	free(*gotos);
	*gotos = NULL;
}
