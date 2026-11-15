/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_lr_state.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:38:51 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:08:55 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERATOR_LR_STATE_H
# define GENERATOR_LR_STATE_H

# include "grammar_rule_state.h"
# include "generator.h"
# include "libft.h"

// vector of t_rule_state (aka itemset aka state in LR parsing theory)
typedef t_vector	t_lr_state;

void	lr_state_init(t_lr_state *lr_state);
void	lr_state_free(void *lr_state);

void	lr_state_table_init(t_vector *lr_states);
void	lr_state_table_free(t_vector *lr_states);

bool	lr_state_add(
			t_vector *lr_states,
			const t_lr_state *lr_state,
			bool *did_add);
bool	lr_state_add_rule_state(
			t_lr_state *lr_state,
			const t_rule_state *rule_state,
			bool *did_add);
bool	lr_state_find_id(
			const t_vector *lr_states,
			const t_lr_state *lr_state,
			size_t *id);
bool	lr_state_complete(
			const t_lr_generator *generator,
			t_lr_state *lr_state);
bool	lr_state_next(
			const t_lr_generator *generator,
			t_lr_state *dst,
			const t_lr_state *src,
			t_symbol symbol);

#endif
