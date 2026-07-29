#include "generator_expects.h"
#include "generator_lr_state.h"
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
# include <assert.h>	// DEBUG

#define EXPECTS_TOO_BIG	"generator: expects table size overflow\n"

static inline bool	expects_report_overflow(void)
{
	(void)write(STDERR_FILENO, EXPECTS_TOO_BIG, str_len(EXPECTS_TOO_BIG));
	return (false);
}

static inline bool	expects_cmd_name_or_word(
						const t_rule rules[RULE_COUNT],
						const t_lr_state *lr_state)
{
	size_t				i;
	const t_rule_state	*rule_state;
	const t_rule		*rule;
	size_t				pos;

	i = 0;
	while (i < lr_state->len)
	{
		rule_state = &((const t_rule_state *)lr_state->data)[i];
		rule = &rules[rule_state->rule_id];
		pos = rule_state->pos;
		if (pos < rule->rhs_len
			&& rule->rhs[pos] == SYM_WORD
			&& (rule->lhs == SYM_cmd_name || rule->lhs == SYM_cmd_word))
			return (true);
		i++;
	}
	return (false);
}

bool	expects_build_table(
			bool **expects_table,
			const t_rule rules[RULE_COUNT],
			const t_vector *lr_states)
{
	size_t				lr_state_id;
	const t_lr_state	*lr_state;
	bool				*entry;

	assert(expects_table != NULL);
	if (lr_states->len > SIZE_MAX / sizeof(**expects_table))
		return (expects_report_overflow());
	*expects_table = malloc(lr_states->len * sizeof(**expects_table));
	if (*expects_table == NULL)
		return (perror("generator"), false);
	lr_state_id = 0;
	while (lr_state_id < lr_states->len)
	{
		lr_state = &((const t_lr_state *)lr_states->data)[lr_state_id];
		entry = &(*expects_table)[lr_state_id];
		*entry = expects_cmd_name_or_word(rules, lr_state);
		lr_state_id++;
	}
	return (true);
}
