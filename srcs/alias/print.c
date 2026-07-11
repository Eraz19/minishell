#include <stdlib.h>
#include "libft.h"
#include "error.h"
#include "alias.h"

void	alias_print_all(const t_key_value **pairs)
{
	size_t	i;

	if (pairs == NULL)
		return ;
	i = 0;
	while (pairs[i] != NULL)
	{
		if (pairs[i]->value == NULL)
			ft_printf("%s=''\n", pairs[i]->key);
		else
			ft_printf("%s='%s'\n", pairs[i]->key, (char *)pairs[i]->value);
		i++;	
	}
	free(pairs);
}

t_error	alias_print_one(t_alias *alias, const char *name)
{
	const char			*value;
	const t_key_value	**pairs;
	t_key_value			*new_key_value;
	union ptr_discalifier
	{
		void *ptr;
		const char *str;
	}	discalifier;

	value = hashmap_get_const(&alias->map, name);
	if (value == NULL)
		return (alias->err = error(ERR_ALIAS_NOT_FOUND));
	pairs = malloc(sizeof(t_key_value *) * 2);
	if (pairs == NULL)
		return (alias->err = error_sys());
	discalifier.str = value;
	new_key_value = key_value_new(name, discalifier.ptr);
	if (new_key_value == NULL)
	{
		alias->err = error_sys();
		return (key_value_free(&new_key_value, NULL), free(pairs), alias->err);
	}
	pairs[0] = new_key_value;
	pairs[1] = NULL;
	return (alias_print_all(pairs), alias->err);
}
