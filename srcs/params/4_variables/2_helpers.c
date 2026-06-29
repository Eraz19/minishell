#include "libft.h"
#include "variables.h"
#include "variables_priv.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG

bool	var_find(const t_var_list *variables, const t_string *name, size_t *res)
{
	size_t	i;
	t_var	*curr;

	assert(variables != NULL);
	i = 0;
	while (i < variables->len)
	{
		curr = &((t_var *)variables->data)[i];
		if (string_cmp(name, &curr->name) == 0)
		{
			*res = i;
			return (true);
		}
		i++;
	}
	return (false);
}

bool	var_find_from_const(
			const t_var_list *variables,
			const char *name,
			size_t *res)
{
	size_t	i;
	t_var	*curr;

	assert(variables != NULL);
	i = 0;
	while (i < variables->len)
	{
		curr = &((t_var *)variables->data)[i];
		if (str_cmp(name, curr->name.data) == 0)
		{
			*res = i;
			return (true);
		}
		i++;
	}
	return (false);
}
