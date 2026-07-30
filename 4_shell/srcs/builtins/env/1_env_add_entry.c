#include "env_priv.h"
#include <stdlib.h>

// @ret ERR_LIBC
t_error	env_add_entry(const char *entry, t_vector *out_envp)
{
	char	*new_entry;
	t_error	err;

	new_entry = str_dup(entry);
	if (new_entry == NULL)
		return (error_sys());
	if (vector_push(out_envp, &new_entry))
		return (error(ERR_NO));
	err = error_sys();
	free(new_entry);
	return (err);
}
