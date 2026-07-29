#ifndef GENERATOR_ACTIONS_PRIV_H
# define GENERATOR_ACTIONS_PRIV_H

# include "generator_actions.h"

bool	action_is_conflict(
			const t_action *action,
			t_action_type new_action_type,
			size_t new_payload);
bool	action_build_default_table(t_action **actions, size_t lr_states_count);

# endif
