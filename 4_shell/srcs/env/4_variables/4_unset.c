#include "libft.h"
#include "shell.h"
#include "variables.h"
#include "variables_priv.h"
#include "utils.h"
#include <stdlib.h>
#include <assert.h>	// DEBUG

t_error	var_unset(const t_string *name)
{
	t_params	*params;
	t_var_list	*list;
	const t_var	*var;

	assert(name != NULL);
	if (!name_is_valid_str(name))
		return (error(ERR_VAR_INVALID_NAME));
	params = shell_get_params();
	assert(params != NULL);
	list = &params->variables;
	var = hashmap_get(list, name->data);
	if (var == NULL)
		return (error(ERR_NO));
	if (var->readonly)
		return (error(ERR_VAR_READ_ONLY));
	(void)hashmap_remove(list, name->data);
	if (str_cmp(name->data, "PATH") == 0)
		cmd_cache_clear(&params->cmd_cache);
	return (error(ERR_NO));
}
