#include "lr_machine_type.h"
#include "parser_type.h"
#include "rule_state_type.h"
#include "lr_state_type.h"
#include "qualifiers_priv.h"
#include <stdlib.h>

// TODO: split in multiple_files

/* ---------- DEBUG (START) ---------- */

# include <stdio.h>	// DEBUG

static inline size_t	qualifier_current_priority(t_qualifier_id qualifier_id)
{
	if (qualifier_id == QUALIFIER_7A || qualifier_id == QUALIFIER_7B)
		return (7);
	else if (qualifier_id == QUALIFIER_6A || qualifier_id == QUALIFIER_6B)
		return (6);
	return (0);
}

static inline void	detect_qualifier_conflict(t_qualifier_id current, t_qualifier_id new)
{
	size_t	current_priority;

	if (current == new)
		return ;
	current_priority = qualifier_current_priority(current);
	if (current_priority == 0)
		return ;
	if (qualifier_current_priority(new) == current_priority)
	{
		fprintf(stderr, "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		fprintf(stderr, "[ERROR] conflict of qualifiers %zu\n", current_priority);
		fprintf(stderr, "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	}
}

/* ---------- DEBUG (END) ---------- */

static inline bool	should_apply_qualifier_word(
	t_lr_machine *machine,
	size_t lr_state_id)
{
	return (machine->actions[lr_state_id][SYM_WORD].type != ACTION_ERROR);
}

static inline bool should_apply_qualifier_1(
	t_lr_machine *machine,
	size_t lr_state_id)
{
	if (machine->actions[lr_state_id][SYM_WORD].type != ACTION_ERROR)
		return (false);
	if (machine->actions[lr_state_id][SYM_NAME].type != ACTION_ERROR)
		return (false);
	if (machine->actions[lr_state_id][SYM_ASSIGNMENT_WORD].type != ACTION_ERROR)
		return (false);
	return (true);
}

static inline bool	rule_is_at_target(
	t_rule_state *rule_state,
	t_rule_id rule_id,
	size_t target_pos)
{
	return (rule_state->rule_id == rule_id && rule_state->pos == target_pos);
}

static inline t_qualifier_id	qualifier_default_id(
	t_lr_machine *machine,
	t_rule_state *rule_state)
{
	t_rule	*rule;

	rule = &machine->rules[rule_state->rule_id];
	if (rule_state->pos >= rule->rhs_len)
		return (QUALIFIER_NONE);
	if (rule->rhs[rule_state->pos] == SYM_WORD)
		return (QUALIFIER_WORD);
	return (QUALIFIER_NONE);
}

static inline t_qualifier_id	qualifier_6_choose_variant(
	t_lr_machine *machine,
	size_t lr_state_id)
{
	t_lr_state		*lr_state;
	t_rule_state	*rule_state;
	t_rule			*rule;
	size_t			i;

	lr_state = &((t_lr_state *)machine->lr_states.data)[lr_state_id];
	i = 0;
	while (i < lr_state->len)
	{
		rule_state = &((t_rule_state *)lr_state->data)[i];
		rule = &machine->rules[rule_state->rule_id];
		if (rule_state->pos < rule->rhs_len)
		{
			if (rule->lhs == SYM_case_clause && rule->rhs[rule_state->pos] == SYM_in)
				return (QUALIFIER_6A);
			else if (rule->lhs == SYM_for_clause && rule->rhs[rule_state->pos] == SYM_in)
				return (QUALIFIER_6B);
			else if (rule->lhs == SYM_for_clause && rule->rhs[rule_state->pos] == SYM_do_group)
				return (QUALIFIER_6B);
		}
		i++;
	}
	return (QUALIFIER_NONE);
}

static inline t_qualifier_id	qualifiers_get_id(
	t_lr_machine *machine,
	size_t lr_state_id,
	t_rule_state *rule_state)
{
	// if (rule_is_at_target(rule_state, RULE_FNAME_1, 0))
	// 	return (QUALIFIER_8);
	if (rule_is_at_target(rule_state, RULE_CMD_NAME_1, 0))
		return (QUALIFIER_7A);
	else if (rule_is_at_target(rule_state, RULE_CMD_WORD_1, 0))
		return (QUALIFIER_7B);
	else if (rule_is_at_target(rule_state, RULE_IN_1, 0))
		return (qualifier_6_choose_variant(machine, lr_state_id));
	else if (rule_is_at_target(rule_state, RULE_DO_GROUP_1, 0))
		return (qualifier_6_choose_variant(machine, lr_state_id));
	else if (rule_is_at_target(rule_state, RULE_NAME_1, 0))
		return (QUALIFIER_5);
	else if (rule_is_at_target(rule_state, RULE_PATTERN_LIST_1, 0))
		return (QUALIFIER_4);
	else if (rule_is_at_target(rule_state, RULE_HERE_END_1, 0))
		return (QUALIFIER_3);
	else if (rule_is_at_target(rule_state, RULE_PATTERN_LIST_2, 1))
		return (QUALIFIER_WORD);
	else if (rule_is_at_target(rule_state, RULE_PATTERN_LIST_3, 2))
		return (QUALIFIER_WORD);
	else if (rule_is_at_target(rule_state, RULE_FILENAME_1, 0))
		return (QUALIFIER_2);
	return (qualifier_default_id(machine, rule_state));
}

static inline void	qualifiers_set_entry_func(
	t_parser *parser,
	t_lr_machine *machine,
	size_t lr_state_id,
	t_qualifier_id qualifier_id)
{
	parser->qualifiers[lr_state_id] = NULL;
	/*
	** @note	qualify_8 has been disabled since fname has been replaced by 
	**			WORD in grammar (name validation is now applied on 
	**			function_definition reduction)
	*/
	// if (qualifier_id == QUALIFIER_8)
	// 	parser->qualifiers[lr_state_id] = qualify_8;
	if (qualifier_id == QUALIFIER_7A)
		parser->qualifiers[lr_state_id] = qualify_7a;
	else if (qualifier_id == QUALIFIER_7B)
		parser->qualifiers[lr_state_id] = qualify_7b;
	else if (qualifier_id == QUALIFIER_6A)
		parser->qualifiers[lr_state_id] = qualify_6a;
	else if (qualifier_id == QUALIFIER_6B)
		parser->qualifiers[lr_state_id] = qualify_6b;
	else if (qualifier_id == QUALIFIER_5)
		parser->qualifiers[lr_state_id] = qualify_5;
	else if (qualifier_id == QUALIFIER_4)
		parser->qualifiers[lr_state_id] = qualify_4;
	else if (qualifier_id == QUALIFIER_3)
		parser->qualifiers[lr_state_id] = qualify_word;
	else if (qualifier_id == QUALIFIER_WORD)
		parser->qualifiers[lr_state_id] = qualify_word;
	else if (qualifier_id == QUALIFIER_2)
		parser->qualifiers[lr_state_id] = qualify_2;
	else if (should_apply_qualifier_word(machine, lr_state_id))
		parser->qualifiers[lr_state_id] = qualify_word;
	else if (should_apply_qualifier_1(machine, lr_state_id))
		parser->qualifiers[lr_state_id] = qualify_1;
}

static inline void	qualifiers_build_entry(
	t_parser *parser,
	t_lr_machine *machine,
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
		detect_qualifier_conflict(qualifier_id, curr_qualifier_id);
		if (curr_qualifier_id > qualifier_id)
			qualifier_id = curr_qualifier_id;
		i++;
	}
	qualifiers_set_entry_func(parser, machine, lr_state_id, qualifier_id);
}

t_error	qualifiers_build_table(t_parser *parser, t_lr_machine *machine)
{
	size_t		state_count;
	size_t		lr_state_id;

	state_count = machine->lr_states.len;
	parser->qualifiers = malloc(state_count * sizeof(*parser->qualifiers));
	if (!parser->qualifiers)
		return (error_sys());
	lr_state_id = 0;
	while (lr_state_id < state_count)
	{
		qualifiers_build_entry(parser, machine, lr_state_id);
		lr_state_id++;
	}
	return (error(ERR_NO));
}
