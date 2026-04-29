#include "parser.h"

static void	parser_rules_init_compound_command_1(t_rule *rules);
static void	parser_rules_init_compound_command_2(t_rule *rules);
static void	parser_rules_init_compound_command_3(t_rule *rules);
static void	parser_rules_init_compound_command_4(t_rule *rules);

/*
compound_command : brace_group
                 | subshell
                 | for_clause
                 | case_clause
                 | if_clause
                 | while_clause
                 | until_clause
                 ;
*/
void	parser_rules_init_compound_command(t_rule *rules)
{
	parser_rules_init_compound_command_1(rules);
	parser_rules_init_compound_command_2(rules);
	parser_rules_init_compound_command_3(rules);
	parser_rules_init_compound_command_4(rules);
}

// compound_command -> brace_group
static void	parser_rules_init_compound_command_1(t_rule *rules)
{
	rules[RULE_COMPOUND_COMMAND_1].lhs = SYM_compound_command;
	rules[RULE_COMPOUND_COMMAND_1].rhs[0] = SYM_brace_group;
	rules[RULE_COMPOUND_COMMAND_1].rhs_len = 1;
}

// compound_command -> subshell
static void	parser_rules_init_compound_command_2(t_rule *rules)
{
	rules[RULE_COMPOUND_COMMAND_2].lhs = SYM_compound_command;
	rules[RULE_COMPOUND_COMMAND_2].rhs[0] = SYM_subshell;
	rules[RULE_COMPOUND_COMMAND_2].rhs_len = 1;
}

// compound_command -> for_clause
// compound_command -> case_clause
static void	parser_rules_init_compound_command_3(t_rule *rules)
{
	rules[RULE_COMPOUND_COMMAND_3].lhs = SYM_compound_command;
	rules[RULE_COMPOUND_COMMAND_3].rhs[0] = SYM_for_clause;
	rules[RULE_COMPOUND_COMMAND_3].rhs_len = 1;
	rules[RULE_COMPOUND_COMMAND_4].lhs = SYM_compound_command;
	rules[RULE_COMPOUND_COMMAND_4].rhs[0] = SYM_case_clause;
	rules[RULE_COMPOUND_COMMAND_4].rhs_len = 1;
}

// compound_command -> if_clause
// compound_command -> while_clause
// compound_command -> until_clause
static void	parser_rules_init_compound_command_4(t_rule *rules)
{
	rules[RULE_COMPOUND_COMMAND_5].lhs = SYM_compound_command;
	rules[RULE_COMPOUND_COMMAND_5].rhs[0] = SYM_if_clause;
	rules[RULE_COMPOUND_COMMAND_5].rhs_len = 1;
	rules[RULE_COMPOUND_COMMAND_6].lhs = SYM_compound_command;
	rules[RULE_COMPOUND_COMMAND_6].rhs[0] = SYM_while_clause;
	rules[RULE_COMPOUND_COMMAND_6].rhs_len = 1;
	rules[RULE_COMPOUND_COMMAND_7].lhs = SYM_compound_command;
	rules[RULE_COMPOUND_COMMAND_7].rhs[0] = SYM_until_clause;
	rules[RULE_COMPOUND_COMMAND_7].rhs_len = 1;
}
