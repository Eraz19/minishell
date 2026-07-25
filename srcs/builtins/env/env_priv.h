#ifndef ENV_PRIV_H
# define ENV_PRIV_H

# include "libft.h"
# include "error.h"

// @ret ERR_LIBC
t_error	env_add_entry(const char *entry, t_vector *out_envp);

// @ret ERR_LIBC
t_error	env_init_envp(char **envp, bool i_is_active, t_vector *out_envp);

// @ret ERR_LIBC
t_error	env_update_envp(char **argv, int count, t_vector *out_envp);

// @ret ERR_POSIX_WRITE
t_error	env_print(t_vector *envp, int *exit_status);

#endif
