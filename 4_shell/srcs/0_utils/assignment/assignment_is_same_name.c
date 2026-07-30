#include <stdbool.h>
#include <stddef.h>

bool	assignment_is_same_name(const char *target, const char *entry)
{
	size_t	i;

	i = 0;
	while (target[i] == entry[i] && target[i] != '=')
		i++;
	return (target[i] == entry[i]);
}
