/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_actions.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:31:47 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/04 16:31:48 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERATOR_ACTIONS_H
# define GENERATOR_ACTIONS_H

# include "libft.h"
# include "grammar_actions.h"
# include "grammar_rules.h"
# include <stdbool.h>
# include <stddef.h>

void	action_init(t_action **actions);
void	action_free(t_action **actions);

bool	action_build_table(
			const t_rule rules[RULE_COUNT],
			const t_vector *lr_states,
			const t_vector *transitions,
			t_action **actions);

#endif
