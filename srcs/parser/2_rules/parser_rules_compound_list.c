#include "parser.h"

static void	parser_rules_init_compound_list_1(t_rule *rules);
static void	parser_rules_init_compound_list_2(t_rule *rules);

/*
compound_list    : linebreak term
                 | linebreak term separator
                 ;
*/
void	parser_rules_init_compound_list(t_rule *rules)
{
	parser_rules_init_compound_list_1(rules);
	parser_rules_init_compound_list_2(rules);
}

// compound_list -> linebreak term
static void	parser_rules_init_compound_list_1(t_rule *rules)
{
	rules[RULE_COMPOUND_LIST_1].lhs = SYM_compound_list;
	rules[RULE_COMPOUND_LIST_1].rhs[0] = SYM_linebreak;
	rules[RULE_COMPOUND_LIST_1].rhs[1] = SYM_term;
	rules[RULE_COMPOUND_LIST_1].rhs_len = 2;
}

// compound_list -> linebreak term separator
static void	parser_rules_init_compound_list_2(t_rule *rules)
{
	rules[RULE_COMPOUND_LIST_2].lhs = SYM_compound_list;
	rules[RULE_COMPOUND_LIST_2].rhs[0] = SYM_linebreak;
	rules[RULE_COMPOUND_LIST_2].rhs[1] = SYM_term;
	rules[RULE_COMPOUND_LIST_2].rhs[2] = SYM_separator;
	rules[RULE_COMPOUND_LIST_2].rhs_len = 3;
}
