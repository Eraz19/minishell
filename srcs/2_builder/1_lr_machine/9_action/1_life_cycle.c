#include "builder.h"
#include <stdlib.h>

void	action_init(t_action ***actions)
{
	*actions = NULL;
}

void	action_free(size_t lr_states_count, t_action ***actions)
{
	size_t	i;

	if (!actions || !*actions)
		return ;
	i = 0;
	while (i < lr_states_count)
	{
		free((*actions)[i]);
		i++;
	}
	free(*actions);
	*actions = NULL;
}
