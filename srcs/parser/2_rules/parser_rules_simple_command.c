#include "parser.h"

static void	parser_rules_init_simple_command_1(t_rule *rules);
static void	parser_rules_init_simple_command_2(t_rule *rules);
static void	parser_rules_init_simple_command_3(t_rule *rules);
static void	parser_rules_init_simple_command_4(t_rule *rules);

/*
simple_command   : cmd_prefix cmd_word cmd_suffix
                 | cmd_prefix cmd_word
                 | cmd_prefix
                 | cmd_name cmd_suffix
                 | cmd_name
                 ;
*/
void	parser_rules_init_simple_command(t_rule *rules)
{
	parser_rules_init_simple_command_1(rules);
	parser_rules_init_simple_command_2(rules);
	parser_rules_init_simple_command_3(rules);
	parser_rules_init_simple_command_4(rules);
}

// simple_command -> cmd_prefix cmd_word cmd_suffix
static void	parser_rules_init_simple_command_1(t_rule *rules)
{
	rules[RULE_SIMPLE_COMMAND_1].lhs = SYM_simple_command;
	rules[RULE_SIMPLE_COMMAND_1].rhs[0] = SYM_cmd_prefix;
	rules[RULE_SIMPLE_COMMAND_1].rhs[1] = SYM_cmd_word;
	rules[RULE_SIMPLE_COMMAND_1].rhs[2] = SYM_cmd_suffix;
	rules[RULE_SIMPLE_COMMAND_1].rhs_len = 3;
}

// simple_command -> cmd_prefix cmd_word
static void	parser_rules_init_simple_command_2(t_rule *rules)
{
	rules[RULE_SIMPLE_COMMAND_2].lhs = SYM_simple_command;
	rules[RULE_SIMPLE_COMMAND_2].rhs[0] = SYM_cmd_prefix;
	rules[RULE_SIMPLE_COMMAND_2].rhs[1] = SYM_cmd_word;
	rules[RULE_SIMPLE_COMMAND_2].rhs_len = 2;
}

// simple_command -> cmd_prefix
// simple_command -> cmd_name cmd_suffix
static void	parser_rules_init_simple_command_3(t_rule *rules)
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
static void	parser_rules_init_simple_command_4(t_rule *rules)
{
	rules[RULE_SIMPLE_COMMAND_5].lhs = SYM_simple_command;
	rules[RULE_SIMPLE_COMMAND_5].rhs[0] = SYM_cmd_name;
	rules[RULE_SIMPLE_COMMAND_5].rhs_len = 1;
}
