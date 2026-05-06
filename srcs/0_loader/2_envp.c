#include "loader.h"
#include "variable.h"
#include <stdlib.h>

bool	loader_parse_envp(t_state *state, char **envp)
{
	size_t	i;
	t_var	var;

	if (!envp)
		return (true);
	i = 0;
	while (envp[i])
	{
		var = (t_var){ 0 };
		var.exported = true;
		if (!var_split(&var.name, &var.value, envp[i]))
			return (false);
		if (!var_name_is_valid(var.name))
			var_free(&var);
		else if (!vector_push(&state->variables, &var))
			return (var_free(&var), false);
		i++;
	}
	return (true);
}
