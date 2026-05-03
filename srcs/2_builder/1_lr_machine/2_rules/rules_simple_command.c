#include "parser.h"

static void	rules_build_simple_command_1(t_rule *rules);
static void	rules_build_simple_command_2(t_rule *rules);
static void	rules_build_simple_command_3(t_rule *rules);
static void	rules_build_simple_command_4(t_rule *rules);

/*
simple_command   : cmd_prefix cmd_word cmd_suffix
                 | cmd_prefix cmd_word
                 | cmd_prefix
                 | cmd_name cmd_suffix
                 | cmd_name
                 ;
*/
void	rules_build_simple_command(t_rule *rules)
{
	rules_build_simple_command_1(rules);
	rules_build_simple_command_2(rules);
	rules_build_simple_command_3(rules);
	rules_build_simple_command_4(rules);
}

// simple_command -> cmd_prefix cmd_word cmd_suffix
static void	rules_build_simple_command_1(t_rule *rules)
{
	rules[RULE_SIMPLE_COMMAND_1].lhs = SYM_simple_command;
	rules[RULE_SIMPLE_COMMAND_1].rhs[0] = SYM_cmd_prefix;
	rules[RULE_SIMPLE_COMMAND_1].rhs[1] = SYM_cmd_word;
	rules[RULE_SIMPLE_COMMAND_1].rhs[2] = SYM_cmd_suffix;
	rules[RULE_SIMPLE_COMMAND_1].rhs_len = 3;
}

// simple_command -> cmd_prefix cmd_word
static void	rules_build_simple_command_2(t_rule *rules)
{
	rules[RULE_SIMPLE_COMMAND_2].lhs = SYM_simple_command;
	rules[RULE_SIMPLE_COMMAND_2].rhs[0] = SYM_cmd_prefix;
	rules[RULE_SIMPLE_COMMAND_2].rhs[1] = SYM_cmd_word;
	rules[RULE_SIMPLE_COMMAND_2].rhs_len = 2;
}

// simple_command -> cmd_prefix
// simple_command -> cmd_name cmd_suffix
static void	rules_build_simple_command_3(t_rule *rules)
{
	rules[RULE_SIMPLE_COMMAND_3].lhs = SYM_simple_command;
	rules[RULE_SIMPLE_COMMAND_3].rhs[0] = SYM_cmd_prefix;
	rules[RULE_SIMPLE_COMMAND_3].rhs_len = 1;
	rules[RULE_SIMPLE_COMMAND_4].lhs = SYM_simple_command;
	rules[RULE_SIMPLE_COMMAND_4].rhs[0] = SYM_cmd_name;
	rules[RULE_SIMPLE_COMMAND_4].rhs[1] = SYM_cmd_suffix;
	rules[RULE_SIMPLE_COMMAND_4].rhs_len = 2;
}

// simple_command -> cmd_name
static void	rules_build_simple_command_4(t_rule *rules)
{
	rules[RULE_SIMPLE_COMMAND_5].lhs = SYM_simple_command;
	rules[RULE_SIMPLE_COMMAND_5].rhs[0] = SYM_cmd_name;
	rules[RULE_SIMPLE_COMMAND_5].rhs_len = 1;
}
