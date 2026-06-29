#include "libft.h"
# include <assert.h>	// DEBUG
# include <stdio.h>	// DEBUG

bool	name_is_valid(const t_string *name)
{
	size_t	i;

	assert(name != NULL);
	fprintf(stderr, "[%s()] checking name [%s]\n", __func__, name->data);
	if (name->len == 0)
		return (false);
	if (!ft_isalpha(name->data[0]) && name->data[0] != '_')
		return (false);
	i = 1;
	while (i < name->len)
	{
		if (!ft_isalnum(name->data[i]) && name->data[i] != '_')
			return (false);
		i++;
	}
	fprintf(stderr, "[%s()] => VALID\n", __func__);
	return (true);
}

bool	name_is_valid_from_const(const char *name)
{
	size_t	i;

	assert(name != NULL);
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
