/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_shell_life_cycle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:56:42 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:56:43 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_priv.h"
#include "lr_tables.h"
#include <stdlib.h>
#include <assert.h>

void	shell_init(t_shell *shell)
{
	shell->is_subshell = false;
	env_init(&shell->params);
	lr_tables_init(&shell->lr_tables);
	history_init(&shell->history);
	shell->runner = NULL;
	shell->last_runner = NULL;
}

void	shell_clear(void)
{
	t_shell	*shell;

	shell = shell_get();
	assert(shell != NULL);
	shell->is_subshell = false;
	env_clear(&shell->params);
	while (shell->runner != NULL)
		(void)shell_destroy_last_instance();
}

void	shell_free(t_shell *shell)
{
	env_free(&shell->params);
	history_free(&shell->history);
	while (shell->runner != NULL)
		(void)shell_destroy_last_instance();
}

void	shell_free_void(void)
{
	t_shell	*shell;

	shell = shell_get();
	if (shell != NULL)
		shell_free(shell);
}
