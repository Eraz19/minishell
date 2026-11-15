/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_sig_action_life_cycle.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:13:03 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:13:04 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig_action.h"

void	sig_action_init(t_sig_action *action)
{
	action->type = SIG_DEFAULT;
	(void)string_init(&action->cmd, 0, NULL, 0);
}

void	sig_action_free(t_sig_action *action)
{
	action->type = SIG_DEFAULT;
	string_free(&action->cmd);
}
