#include "parser.h"

static void	rules_build_complete_command_1(t_rule *rules);
static void	rules_build_complete_command_2(t_rule *rules);

/*
complete_command : list separator_op
                 | list
                 ;
*/
void	rules_build_complete_command(t_rule *rules)
{
	rules_build_complete_command_1(rules);
	rules_build_complete_command_2(rules);
}

// complete_command -> list separator_op
static void	rules_build_complete_command_1(t_rule *rules)
{
	rules[RULE_COMPLETE_COMMAND_1].lhs = SYM_complete_command;
	rules[RULE_COMPLETE_COMMAND_1].rhs[0] = SYM_list;
	rules[RULE_COMPLETE_COMMAND_1].rhs[1] = SYM_separator_op;
	rules[RULE_COMPLETE_COMMAND_1].rhs_len = 2;
}

// complete_command -> list
static void	rules_build_complete_command_2(t_rule *rules)
{
	rules[RULE_COMPLETE_COMMAND_2].lhs = SYM_complete_command;
	rules[RULE_COMPLETE_COMMAND_2].rhs[0] = SYM_list;
	rules[RULE_COMPLETE_COMMAND_2].rhs_len = 1;
}
