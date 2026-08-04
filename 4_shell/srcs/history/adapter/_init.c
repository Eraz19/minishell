/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:08:10 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:15:01 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // IWYU pragma: keep
#include <readline/readline.h>
#include "history_adapter.h"

void	history_adapter_init(t_history_adapter *history_adapter)
{
	history_adapter->count = 0;
}

void	history_adapter_free(t_history_adapter *history_adapter)
{
	rl_clear_history();
	history_adapter->count = 0;
}

void	history_adapter_load(
			t_history_adapter *history_adapter,
			t_history_list *history_list)
{
	return (add_to_readline_history(
			history_adapter,
			history_list, history_list->len));
}
