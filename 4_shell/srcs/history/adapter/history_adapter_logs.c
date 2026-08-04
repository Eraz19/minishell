/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_adapter_logs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:08:12 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:08:13 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logs.h" // DEBUG
#include "history_adapter.h"

void	success_history_adapter_add_log(t_history_adapter *history_adapter)
{
	print_pass("entries uploaded to readline           %i\n", (int)history_adapter->count);
}
