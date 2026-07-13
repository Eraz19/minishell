#include "env_.h"

static const char	*env_last_override(const char *entry,
						const t_env_args *args)
{
	size_t		i;
	const char	*found;

	found = NULL;
	i = 0;
	while (i < args->assign_count)
	{
		if (env_same_name(entry, args->assigns[i]))
			found = args->assigns[i];
		i++;
	}
	return (found);
}

static bool	env_in_envp(const char *assign, char **envp)
{
	size_t	i;

	i = 0;
	while (envp != NULL && envp[i] != NULL)
	{
		if (env_same_name(assign, envp[i]))
			return (true);
		i++;
	}
	return (false);
}

static bool	env_is_first_of_name(const char *assign, size_t i,
				const t_env_args *args)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		if (env_same_name(assign, args->assigns[j]))
			return (false);
		j++;
	}
	return (true);
}

static t_error	env_print_new(char **envp, const t_env_args *args)
{
	size_t	i;
	t_error	err;

	err = error(ERR_NO);
	i = 0;
	while (err.type == ERR_NO && i < args->assign_count)
	{
		if (!env_in_envp(args->assigns[i], envp)
			&& env_is_first_of_name(args->assigns[i], i, args))
			err = env_print_entry(env_last_override(args->assigns[i], args));
		i++;
	}
	return (err);
}

t_error	env_print(char **envp, const t_env_args *args)
{
	size_t		i;
	t_error		err;
	const char	*line;

	err = error(ERR_NO);
	i = 0;
	while (err.type == ERR_NO && envp != NULL && envp[i] != NULL)
	{
		line = env_last_override(envp[i], args);
		if (line == NULL)
			line = envp[i];
		err = env_print_entry(line);
		i++;
	}
	if (err.type == ERR_NO)
		err = env_print_new(envp, args);
	return (err);
}
