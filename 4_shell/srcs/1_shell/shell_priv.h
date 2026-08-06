/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_priv.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:57:02 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:57:03 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_PRIV_H
# define SHELL_PRIV_H

# include "shell.h"

typedef struct s_shell_loading_options
{
	t_shell	*shell;
	int 	argc;
	char	**argv;
	char	**envp;
}	t_shell_loading_options;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @brief Initializes a shell state in place.
 *
 * @param shell Destination shell object initialized by the function (borrowed).
 */
void	shell_init(t_shell *shell);

// TODO: doc
t_error	shell_load(t_shell *shell, int argc, char **argv, char **envp);

/**
 * @brief Releases the global shell state and clears the singleton.
 *
 * Does nothing when no shell is currently registered.
 */
void	shell_free(t_shell *shell);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Handles the ENV startup hook for interactive stdin sessions.
 *
 * @note Non-interactive shells and shells without OPT_STDIN_INPUT active are
 *       skipped.
 * @return ERR_NO on success or no-op, ERR_SHELL_NOT_FOUND if options are
 *         unavailable, or ERR_LIBC on allocation or POSIX failure.
 */
t_error	shell_exec_env(void);

#endif
