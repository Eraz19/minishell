/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_shell_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:56:47 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:39:53 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_priv.h"
#include "sig.h"

t_error	shell_load(t_shell *shell, int argc, char **argv, char **envp)
{
	t_error	err;

	err = env_load(&shell->params, argc, argv, envp);
	if (err.type == ERR_NO)
		err = sig_load();
	if (err.type == ERR_NO)
		err = history_load(&shell->history);
	return (err);
}
