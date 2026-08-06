/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_shell_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:56:40 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:56:41 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

#define DEFAULT_NAME	"minishell"

t_shell	*shell_get(void)
{
	static t_shell shell;

	return (&shell);
}

const char	*shell_get_name(void)
{
	t_shell	*shell;

	shell = shell_get();
	if (!shell)
		return (DEFAULT_NAME);
	return (shell->params.name);
}
