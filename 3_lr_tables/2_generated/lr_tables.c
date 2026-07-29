#include "lr_tables.h"
#include "grammar_rules.h"

void	lr_tables_load(t_lr_tables *tables)
{
	static const t_lr_rule		rules[RULE_COUNT];
	static const t_action		actions[ACTION_COUNT];
	static const size_t			gotos[GOTO_COUNT];
	static const t_qualifier	qualifiers[LR_STATE_COUNT];
	static const bool			expects_cmd_name_or_word[LR_STATE_COUNT];

	tables->rules = rules;
	tables->actions = actions;
	tables->gotos = gotos;
	tables->qualifiers = qualifiers;
	tables->expects_cmd_name_or_word = expects_cmd_name_or_word;
}
