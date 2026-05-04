#include "parser.h"

static void	rules_build_complete_commands_1(t_rule *rules);
static void	rules_build_complete_commands_2(t_rule *rules);

/*
complete_commands: complete_commands newline_list complete_command
                 |                                complete_command
                 ;
*/
void	rules_build_complete_commands(t_rule *rules)
{
	rules_build_complete_commands_1(rules);
	rules_build_complete_commands_2(rules);
}

// complete_commands -> complete_commands newline_list complete_command
static void	rules_build_complete_commands_1(t_rule *rules)
{
	rules[RULE_COMPLETE_COMMANDS_1].lhs = SYM_complete_commands;
	rules[RULE_COMPLETE_COMMANDS_1].rhs[0] = SYM_complete_commands;
	rules[RULE_COMPLETE_COMMANDS_1].rhs[1] = SYM_newline_list;
	rules[RULE_COMPLETE_COMMANDS_1].rhs[2] = SYM_complete_command;
	rules[RULE_COMPLETE_COMMANDS_1].rhs_len = 3;
}

// complete_commands -> complete_command
static void	rules_build_complete_commands_2(t_rule *rules)
{
	rules[RULE_COMPLETE_COMMANDS_2].lhs = SYM_complete_commands;
	rules[RULE_COMPLETE_COMMANDS_2].rhs[0] = SYM_complete_command;
	rules[RULE_COMPLETE_COMMANDS_2].rhs_len = 1;
}
