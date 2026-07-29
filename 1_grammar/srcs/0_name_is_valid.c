#include "grammar_name.h"
#include "libft.h"
#include <assert.h>

bool	name_is_valid(const char *name)
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
