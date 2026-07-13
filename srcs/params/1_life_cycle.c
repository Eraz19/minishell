#include "params.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG

void	params_init(t_params *params)
{
	assert(params != NULL);
	params->name = NULL;
	var_init(&params->variables);
	options_init(&params->options);
	specials_init(&params->specials);
	positionals_init_stack(&params->positionals_stack);
	functions_init(&params->functions);
	process_init(&params->processes);
}

void	params_init_subshell(t_params *params)
{
	process_clear(&params->processes);
}

void	params_free(t_params *params)
{
	assert(params != NULL);
	params->name = NULL;
	var_free(&params->variables);
	options_free(&params->options);
	specials_free(&params->specials);
	positionals_free_stack(&params->positionals_stack);
	functions_free(&params->functions);
	process_free(&params->processes);
}
