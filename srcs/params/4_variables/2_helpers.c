#include "libft.h"
#include "variables.h"
#include "variables_priv.h"
#include <stdlib.h>

bool	var_name_is_valid(const char *name)
{
	size_t	i;

	if (!name || !name[0])
		return (false);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (false);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	var_find(const t_var_list *variables, const char *name, size_t *res)
{
	size_t	i;
	size_t	len;
	t_var	*curr;

	len = 0;
	while (name[len] != '\0')
		len++;
	i = 0;
	while (i < variables->len)
	{
		curr = &((t_var *)variables->data)[i];
		if (str_ncmp(name, curr->name, len + 1) == 0)
		{
			*res = i;
			return (true);
		}
		i++;
	}
	return (false);
}
