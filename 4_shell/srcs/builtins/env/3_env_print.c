#include "env_priv.h"
#include "posix_helpers.h"
#include <unistd.h>

t_error	builtin_env_print(t_vector *envp, int *exit_status)
{
	size_t	i;
	char	*entry;
	t_error	err;

	i = 0;
	while (i < envp->len - 1)
	{
		entry = ((char **)envp->data)[i];
		err = posix_write(STDOUT_FILENO, entry, str_len(entry));
		if (err.type)
			return (err);
		i++;
	}
	*exit_status = 0;
	return (error(ERR_NO));
}
