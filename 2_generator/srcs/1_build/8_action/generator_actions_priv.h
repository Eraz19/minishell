/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_actions_priv.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:15:34 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:17:11 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERATOR_ACTIONS_PRIV_H
# define GENERATOR_ACTIONS_PRIV_H

# include "grammar_actions.h"
# include <stdbool.h>

bool	action_is_conflict(
			const t_action *action,
			t_action_type new_action_type,
			size_t new_payload);
bool	action_build_default_table(t_action **actions, size_t lr_states_count);

#endif
