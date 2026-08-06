/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_life_cycle_function.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:11:31 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 15:07:56 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <stdlib.h>

void	function_init(t_function *function)
{
	ast_command_init(&function->body);
	ast_redir_list_init(&function->redirs);
	function->active_count = 0;
	function->pending_free = false;
}

void	function_free(t_function **function)
{
	if (function == NULL || *function == NULL)
		return ;
	ast_command_free(&(*function)->body);
	ast_redir_list_free(&(*function)->redirs);
	(*function)->active_count = 0;
	(*function)->pending_free = false;
	free(*function);
	*function = NULL;
}
