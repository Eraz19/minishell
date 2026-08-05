/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_load_env_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:09:04 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/05 19:04:19 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "history_load_env_priv.h"

void	on_history_disabled_error(void)
{
	(void)error_print(
		error(ERR_HISTORY_DISABLED),
		"history",
		"no valid history file path found", NULL, NULL);
}
