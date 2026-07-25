#include "env_priv.h"
#include "utils.h"
#include <stdlib.h>

// @ret ERR_LIBC
static inline t_error	env_dup_envp(char **envp, t_vector *out_envp)
{
	size_t	i;
	t_error	err;

	i = 0;
	while (envp[i] != NULL)
	{
		err = env_add_entry(envp[i], out_envp);
		if (err.type)
			return (err);
		i++;
	}
	return (error(ERR_NO));
}

// @ret ERR_LIBC
static inline t_error	env_add_null_terminator(t_vector *out_envp)
{
	char	*null;
	t_error	err;

	null = NULL;
	if (!vector_push(out_envp, &null))
	{
		err = error_sys();
		vector_free(out_envp, free_char_ptr_void);
		return (err);
	}
	return (error(ERR_NO));
}

t_error	env_init_envp(char **envp, bool i_is_active, t_vector *out_envp)
{
	t_error	err;

	(void)vector_init(out_envp, sizeof(*envp), 0);
	err.type = ERR_NO;
	if (i_is_active == false)
		err = env_dup_envp(envp, out_envp);
	if (err.type == ERR_NO)
		err = env_add_null_terminator(out_envp);
	if (err.type)
		vector_free(out_envp, free_char_ptr_void);
	return (err);
}
