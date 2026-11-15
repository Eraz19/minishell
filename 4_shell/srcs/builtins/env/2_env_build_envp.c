/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_env_build_envp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:41:01 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:41:02 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
static inline t_error	env_add_null_terminator(t_vector *out_env)
{
	char	*null;
	t_error	err;

	null = NULL;
	if (!vector_push(out_env, &null))
	{
		err = error_sys();
		vector_free(out_env, free_char_ptr_void);
		return (err);
	}
	return (error(ERR_NO));
}

static inline int	env_get_existing_index(const t_vector *env, const char *arg)
{
	int			i;
	const char	*entry;

	i = 0;
	while ((size_t)i < env->len)
	{
		entry = ((const char **)env->data)[i];
		if (assignment_is_same_name(entry, arg) == true)
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

t_error	builtin_env_build_envp(
			char **envp,
			char **argv,
			int count,
			t_vector *out_envp)
{
	int		i;
	int		existing_entry_index;
	t_error	err;

	(void)vector_init(out_envp, sizeof(char *), 0);
	err.type = ERR_NO;
	if (envp != NULL)
		err = env_dup_envp(envp, out_envp);
	i = 0;
	while (i < count && err.type == ERR_NO)
	{
		existing_entry_index = env_get_existing_index(out_envp, argv[i]);
		if (existing_entry_index >= 0)
			err = env_update_entry(out_envp, existing_entry_index, argv[i]);
		else
			err = env_add_entry(argv[i], out_envp);
		i++;
	}
	if (err.type == ERR_NO)
		err = env_add_null_terminator(out_envp);
	if (err.type)
		vector_free(out_envp, free_char_ptr_void);
	return (err);
}
