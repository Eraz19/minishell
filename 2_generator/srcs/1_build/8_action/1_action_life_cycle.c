#include "generator_actions.h"
#include <stdlib.h>

void	action_init(t_action **actions)
{
	*actions = NULL;
}

void	action_free(t_action **actions)
{
	if (!actions || !*actions)
		return ;
	free(*actions);
	*actions = NULL;
}
