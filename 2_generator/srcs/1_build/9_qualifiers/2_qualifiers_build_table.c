#include "generator_qualifiers.h"
#include "generator_qualifiers_priv.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
# include <assert.h>	// DEBUG

#define QUALIFIERS_TOO_BIG	"generator: qualifiers table size overflow\n"

static inline bool	qualifiers_report_overflow(void)
{
	(void)write(STDERR_FILENO, QUALIFIERS_TOO_BIG, str_len(QUALIFIERS_TOO_BIG));
	return (false);
}

static inline t_qualifier_id	qualifiers_get_id(
									const t_rule rules[RULE_COUNT],
									const t_lr_state *lr_state,
									const t_rule_state *rule_state)
{
	if (qualifier_rule_is_at_target(rule_state, RULE_CMD_NAME_1, 0))
		return (QUALIFIER_7A);
	else if (qualifier_rule_is_at_target(rule_state, RULE_CMD_WORD_1, 0))
		return (QUALIFIER_7B);
	else if (qualifier_rule_is_at_target(rule_state, RULE_IN_1, 0))
		return (qualifier_6_choose_variant(rules, lr_state));
	else if (qualifier_rule_is_at_target(rule_state, RULE_DO_GROUP_1, 0))
		return (qualifier_6_choose_variant(rules, lr_state));
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
	return (qualifier_default_id(rules, rule_state));
}

static inline void	qualifiers_set_entry_func(
						t_qualifier *qualifiers,
						const t_action *actions,
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
	else if (qualifier_should_apply_word(actions, lr_state_id))
		qualifiers[lr_state_id] = qualify_word;
	else if (qualifier_should_apply_1(actions, lr_state_id))
		qualifiers[lr_state_id] = qualify_1;
}

static inline t_qualifier_id	qualifiers_get_entry_id(
									const t_rule rules[RULE_COUNT],
									const t_lr_state *lr_state)
{
	const t_rule_state	*rule_state;
	size_t				i;
	t_qualifier_id		qualifier_id;
	t_qualifier_id		curr_qualifier_id;

	qualifier_id = QUALIFIER_NONE;
	i = 0;
	while (i < lr_state->len)
	{
		rule_state = &((const t_rule_state *)lr_state->data)[i];
		curr_qualifier_id = qualifiers_get_id(rules, lr_state, rule_state);
		if (curr_qualifier_id > qualifier_id)
			qualifier_id = curr_qualifier_id;
		i++;
	}
	return (qualifier_id);
}

bool	qualifiers_build_table(
			t_qualifier **qualifiers,
			const t_rule rules[RULE_COUNT],
			const t_vector *lr_states,
			const t_action *actions)
{
	size_t				state_count;
	size_t				lr_state_id;
	const t_lr_state	*lr_state;
	t_qualifier_id		qualifier_id;

	assert(qualifiers != NULL);
	assert(rules != NULL);
	assert(lr_states != NULL);
	assert(actions != NULL);
	state_count = lr_states->len;
	if (state_count > SIZE_MAX / sizeof(**qualifiers))
		return (qualifiers_report_overflow());
	*qualifiers = malloc(state_count * sizeof(**qualifiers));
	if (*qualifiers == NULL)
		return (perror("generator"), false);
	lr_state_id = 0;
	while (lr_state_id < state_count)
	{
		lr_state = &((const t_lr_state *)lr_states->data)[lr_state_id];
		qualifier_id = qualifiers_get_entry_id(rules, lr_state);
		qualifiers_set_entry_func(
			*qualifiers, actions, lr_state_id, qualifier_id);
		lr_state_id++;
	}
	return (true);
}
