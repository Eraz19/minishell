/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_shell_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:56:44 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 20:51:16 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <assert.h>	// DEBUG

t_history	*shell_get_history(void)
{
	t_shell	*shell;

	shell = shell_get();
	return (&shell->history);
}

t_params	*shell_get_params(void)
{
	t_shell	*shell;

	shell = shell_get();
	return (&shell->params);
}

const t_lr_tables	*shell_get_lr_tables(void)
{
	t_shell	*shell;

	shell = shell_get();
	return (&shell->lr_tables);
}
