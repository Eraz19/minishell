#include <stdbool.h>
#include <stddef.h>

bool	cmd_entry_is_target(const char *target, const char *entry)
{
	size_t	i;

	i = 0;
	while (target[i] == entry[i] && target[i] != '=')
		i++;
	return (target[i] == entry[i]);
}
