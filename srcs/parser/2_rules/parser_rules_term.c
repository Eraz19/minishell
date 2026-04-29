#include "parser.h"

static void	parser_rules_init_term_1(t_rule *rules);
static void	parser_rules_init_term_2(t_rule *rules);

/*
term             : term separator and_or
                 |                and_or
                 ;
*/
void	parser_rules_init_term(t_rule *rules)
{
	parser_rules_init_term_1(rules);
	parser_rules_init_term_2(rules);
}

// term -> term separator and_or
static void	parser_rules_init_term_1(t_rule *rules)
{
	rules[RULE_TERM_1].lhs = SYM_term;
	rules[RULE_TERM_1].rhs[0] = SYM_term;
	rules[RULE_TERM_1].rhs[1] = SYM_separator;
	rules[RULE_TERM_1].rhs[2] = SYM_and_or;
	rules[RULE_TERM_1].rhs_len = 3;
}

// term -> and_or
static void	parser_rules_init_term_2(t_rule *rules)
{
	rules[RULE_TERM_2].lhs = SYM_term;
	rules[RULE_TERM_2].rhs[0] = SYM_and_or;
	rules[RULE_TERM_2].rhs_len = 1;
}
