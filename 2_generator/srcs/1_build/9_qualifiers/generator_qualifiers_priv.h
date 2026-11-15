/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_qualifiers_priv.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:16:31 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:16:32 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERATOR_QUALIFIERS_PRIV_H
# define GENERATOR_QUALIFIERS_PRIV_H

# include "grammar_rules.h"
# include "grammar_rule_state.h"
# include "generator_lr_state.h"
# include "grammar_actions.h"
# include <stdbool.h>
# include <stddef.h>

/*
** @note Qualifier 3 is partially applied via reduce_hook hook_3()
** @note Qualifier 8 has been disabled since fname has been replaced by 
**		WORD in grammar (name validation is now applied on 
**		function_definition reduction)
*/
typedef enum qualifier_id
{
	QUALIFIER_NONE,
	QUALIFIER_WORD,
	QUALIFIER_1,
	QUALIFIER_2,
	QUALIFIER_3,
	QUALIFIER_4,
	QUALIFIER_5,
	QUALIFIER_6A,
	QUALIFIER_6B,
	QUALIFIER_7A,
	QUALIFIER_7B,
	QUALIFIER_8,
	QUALIFIER_COUNT
}	t_qualifier_id;

bool			qualifier_should_apply_word(
					const t_action *actions,
					size_t lr_state_id);
bool			qualifier_should_apply_1(
					const t_action *actions,
					size_t lr_state_id);
bool			qualifier_rule_is_at_target(
					const t_rule_state *rule_state,
					t_rule_id rule_id,
					size_t target_pos);
t_qualifier_id	qualifier_default_id(
					const t_rule rules[RULE_COUNT],
					const t_rule_state *rule_state);
t_qualifier_id	qualifier_6_choose_variant(
					const t_rule rules[RULE_COUNT],
					const t_lr_state *lr_state);

#endif
