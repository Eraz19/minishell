#include "lr_machine_type.h"
#include "rule_state_type.h"
#include "lr_state_type.h"
#include "qualifiers_priv.h"
#include "qualifiers.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG

static inline t_qualifier_id	qualifiers_get_id(
									const t_lr_machine *machine,
									size_t lr_state_id,
									const t_rule_state *rule_state)
{
	if (qualifier_rule_is_at_target(rule_state, RULE_CMD_NAME_1, 0))
		return (QUALIFIER_7A);
	else if (qualifier_rule_is_at_target(rule_state, RULE_CMD_WORD_1, 0))
		return (QUALIFIER_7B);
	else if (qualifier_rule_is_at_target(rule_state, RULE_IN_1, 0))
		return (qualifier_6_choose_variant(machine, lr_state_id));
	else if (qualifier_rule_is_at_target(rule_state, RULE_DO_GROUP_1, 0))
		return (qualifier_6_choose_variant(machine, lr_state_id));
	else if (qualifier_rule_is_at_target(rule_state, RULE_NAME_1, 0))
		return (QUALIFIER_5);
	else if (qualifier_rule_is_at_target(rule_state, RULE_PATTERN_LIST_1, 0))
		return (QUALIFIER_4);
	else if (qualifier_rule_is_at_target(rule_state, RULE_HERE_END_1, 0))
		return (QUALIFIER_3);
	else if (qualifier_rule_is_at_target(rule_state, RULE_PATTERN_LIST_2, 1))
		return (QUALIFIER_WORD);
	else if (qualifier_rule_is_at_target(rule_state, RULE_PATTERN_LIST_3, 2))
		return (QUALIFIER_WORD);
	else if (qualifier_rule_is_at_target(rule_state, RULE_FILENAME_1, 0))
		return (QUALIFIER_2);
	return (qualifier_default_id(machine, rule_state));
}

static inline void	qualifiers_set_entry_func(
						t_qualifier *qualifiers,
						const t_lr_machine *machine,
						size_t lr_state_id,
						t_qualifier_id qualifier_id)
{
	qualifiers[lr_state_id] = NULL;
	if (qualifier_id == QUALIFIER_7A)
		qualifiers[lr_state_id] = qualify_7a;
	else if (qualifier_id == QUALIFIER_7B)
		qualifiers[lr_state_id] = qualify_7b;
	else if (qualifier_id == QUALIFIER_6A)
		qualifiers[lr_state_id] = qualify_6a;
	else if (qualifier_id == QUALIFIER_6B)
		qualifiers[lr_state_id] = qualify_6b;
	else if (qualifier_id == QUALIFIER_5)
		qualifiers[lr_state_id] = qualify_5;
	else if (qualifier_id == QUALIFIER_4)
		qualifiers[lr_state_id] = qualify_4;
	else if (qualifier_id == QUALIFIER_3)
		qualifiers[lr_state_id] = qualify_word;
	else if (qualifier_id == QUALIFIER_WORD)
		qualifiers[lr_state_id] = qualify_word;
	else if (qualifier_id == QUALIFIER_2)
		qualifiers[lr_state_id] = qualify_2;
	else if (qualifier_should_apply_word(machine, lr_state_id))
		qualifiers[lr_state_id] = qualify_word;
	else if (qualifier_should_apply_1(machine, lr_state_id))
		qualifiers[lr_state_id] = qualify_1;
}

static inline void	qualifiers_build_entry(
						t_qualifier *qualifiers,
						const t_lr_machine *machine,
						size_t lr_state_id)
{
	t_lr_state		*lr_state;
	t_rule_state	*rule_state;
	size_t			i;
	t_qualifier_id	qualifier_id;
	t_qualifier_id	curr_qualifier_id;

	lr_state = &((t_lr_state *)machine->lr_states.data)[lr_state_id];
	qualifier_id = QUALIFIER_NONE;
	i = 0;
	while (i < lr_state->len)
	{
		rule_state = &((t_rule_state *)lr_state->data)[i];
		curr_qualifier_id = qualifiers_get_id(machine, lr_state_id, rule_state);
		if (curr_qualifier_id > qualifier_id)
			qualifier_id = curr_qualifier_id;
		i++;
	}
	qualifiers_set_entry_func(qualifiers, machine, lr_state_id, qualifier_id);
}

t_error	qualifiers_build_table(
			t_qualifier **qualifiers,
			const t_lr_machine *machine)
{
	size_t	state_count;
	size_t	lr_state_id;

	assert(qualifiers != NULL);
	assert(machine != NULL);
	state_count = machine->lr_states.len;
	*qualifiers = malloc(state_count * sizeof(**qualifiers));
	if (!*qualifiers)
		return (error_sys());
	lr_state_id = 0;
	while (lr_state_id < state_count)
	{
		qualifiers_build_entry(*qualifiers, machine, lr_state_id);
		lr_state_id++;
	}
	return (error(ERR_NO));
}
