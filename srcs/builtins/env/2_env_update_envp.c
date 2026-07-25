#include "env_priv.h"
#include "utils.h"
#include <stdlib.h>

static inline int	env_get_existing_index(char **envp, const char *arg)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (assignment_is_same_name(envp[i], arg) == true)
			return (i);
		i++;
	}
	return (-1);
}

// @ret ERR_LIBC
static inline t_error	env_update_entry(
							t_vector *out_envp,
							int existing_entry_index,
							const char *new_value)
{
	char	**existing_entry_ptr;

	existing_entry_ptr = &((char **)out_envp->data)[existing_entry_index];
	free(*existing_entry_ptr);
	*existing_entry_ptr = str_dup(new_value);
	if (*existing_entry_ptr == NULL)
		return (error_sys());
	return (error(ERR_NO));
}

t_error	env_update_envp(char **argv, int count, t_vector *out_envp)
{
	int		i;
	int		existing_entry_index;
	t_error	err;

	i = 0;
	err.type = ERR_NO;
	while (i < count && err.type == ERR_NO)
	{
		existing_entry_index = env_get_existing_index(out_envp->data, argv[i]);
		if (existing_entry_index >= 0)
			err = env_update_entry(out_envp, existing_entry_index, argv[i]);
		else
			err = env_add_entry(argv[i], out_envp);
		i++;
	}
	if (err.type)
		vector_free(out_envp, free_char_ptr_void);
	return (err);
}
