#include "params.h"
#include "shell.h"

t_error	params_get_last_status(int *out)
{
	t_params	*params;

	params = shell_get_params();
	if (params == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	*out = params->specials.last_status;
	return (error(ERR_NO));
}
