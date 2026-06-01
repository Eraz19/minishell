#include "params.h"
#include <stdlib.h>

void	params_init(t_params *params)
{
	params->name = NULL;
	var_init(&params->variables);
	options_init(&params->options);
	specials_init(&params->specials);
	positionals_init(&params->positionals);
}

void	params_free(t_params *params)
{
	params->name = NULL;
	var_free(&params->variables);
	options_free(&params->options);
	specials_free(&params->specials);
	positionals_free(&params->positionals);
}
