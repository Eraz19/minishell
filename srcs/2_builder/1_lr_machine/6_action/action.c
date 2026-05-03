#include "parser.h"
#include <stdlib.h>

void	action_init(t_action ***actions)
{
	*actions = NULL;
}

bool	action_build_table(t_lr_machine *machine)
{
	// TODO
}

void	action_free(size_t lr_states_count, size_t ***actions)
{
	size_t	i;

	i = 0;
	while (i < lr_states_count)
	{
		free((*actions)[i]);
		i++;
	}
	free(*actions);
	*actions = NULL;
}
