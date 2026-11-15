/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_rule_state.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:38:57 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/04 16:38:58 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERATOR_RULE_STATE_H
# define GENERATOR_RULE_STATE_H

# include "grammar_rules.h"
# include "grammar_rule_state.h"
# include <stdbool.h>

bool		rule_state_equal(const t_rule_state *a, const t_rule_state *b);
bool		rule_state_is_complete(
				const t_rule *rules,
				const t_rule_state *rule_state);
t_symbol	rule_state_next_symbol(
				const t_rule *rules,
				const t_rule_state *rule_state);

#endif
