/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_priv.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:41:05 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:41:06 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_PRIV_H
# define ENV_PRIV_H

# include "libft.h"
# include "error.h"

// @ret ERR_LIBC
t_error	env_add_entry(const char *entry, t_vector *out_envp);

// @ret ERR_LIBC
t_error	builtin_env_build_envp(
			char **envp,
			char **argv,
			int count,
			t_vector *out_envp);

// @ret ERR_POSIX_WRITE
t_error	builtin_env_print(t_vector *envp, int *exit_status);

#endif
