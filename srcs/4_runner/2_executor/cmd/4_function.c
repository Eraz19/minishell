#include "libft.h"
#include "cmd_priv.h"
#include "functions.h"

bool	cmd_name_is_function(
			t_functions *functions,
			const char *name,
			const t_function **out_function)
{
	t_key_value	*key_value;

	key_value = hashmap_get(functions, name);
	if (key_value == NULL)
		return (false);
	*out_function = key_value->value;
	return (true);
}
