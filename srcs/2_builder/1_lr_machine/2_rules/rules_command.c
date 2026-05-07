#include "parser.h"

static void	rules_build_command_1(t_rule *rules);
static void	rules_build_command_2(t_rule *rules);
static void	rules_build_command_3(t_rule *rules);
static void	rules_build_command_4(t_rule *rules);

/*
command          : simple_command
                 | compound_command
                 | compound_command redirect_list
                 | function_definition
                 ;
*/
void	rules_build_command(t_rule *rules)
{
	rules_build_command_1(rules);
	rules_build_command_2(rules);
	rules_build_command_3(rules);
	rules_build_command_4(rules);
}

// command -> simple_command
static void	rules_build_command_1(t_rule *rules)
{
	rules[RULE_COMMAND_1].lhs = SYM_command;
	rules[RULE_COMMAND_1].rhs[0] = SYM_simple_command;
	rules[RULE_COMMAND_1].rhs_len = 1;
}

// command -> compound_command
static void	rules_build_command_2(t_rule *rules)
{
	rules[RULE_COMMAND_2].lhs = SYM_command;
	rules[RULE_COMMAND_2].rhs[0] = SYM_compound_command;
	rules[RULE_COMMAND_2].rhs_len = 1;
}

// command -> compound_command redirect_list
static void	rules_build_command_3(t_rule *rules)
{
	rules[RULE_COMMAND_3].lhs = SYM_command;
	rules[RULE_COMMAND_3].rhs[0] = SYM_compound_command;
	rules[RULE_COMMAND_3].rhs[1] = SYM_redirect_list;
	rules[RULE_COMMAND_3].rhs_len = 2;
}

// command -> function_definition
static void	rules_build_command_4(t_rule *rules)
{
	rules[RULE_COMMAND_4].lhs = SYM_command;
	rules[RULE_COMMAND_4].rhs[0] = SYM_function_definition;
	rules[RULE_COMMAND_4].rhs_len = 1;
}
