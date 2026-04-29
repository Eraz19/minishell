#include "parser.h"

static void	parser_rules_init_separator_1(t_rule *rules);
static void	parser_rules_init_separator_2(t_rule *rules);

/*
separator        : separator_op linebreak
                 | newline_list
                 ;
*/
void	parser_rules_init_separator(t_rule *rules)
{
	parser_rules_init_separator_1(rules);
	parser_rules_init_separator_2(rules);
}

// separator -> separator_op linebreak
static void	parser_rules_init_separator_1(t_rule *rules)
{
	rules[RULE_SEPARATOR_1].lhs = SYM_separator;
	rules[RULE_SEPARATOR_1].rhs[0] = SYM_separator_op;
	rules[RULE_SEPARATOR_1].rhs[1] = SYM_linebreak;
	rules[RULE_SEPARATOR_1].rhs_len = 2;
}

// separator -> newline_list
static void	parser_rules_init_separator_2(t_rule *rules)
{
	rules[RULE_SEPARATOR_2].lhs = SYM_separator;
	rules[RULE_SEPARATOR_2].rhs[0] = SYM_newline_list;
	rules[RULE_SEPARATOR_2].rhs_len = 1;
}
