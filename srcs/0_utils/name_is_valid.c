#include "libft.h"
# include <assert.h>	// DEBUG

bool	name_is_valid(const t_string *name)
{
	size_t	i;

	assert(name != NULL);
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
	return (true);
}
