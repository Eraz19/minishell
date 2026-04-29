#include "parser.h"

/*
subshell         : '(' compound_list ')'
                 ;
*/
void	parser_rules_init_subshell(t_rule *rules)
{
	rules[RULE_SUBSHELL_1].lhs = SYM_subshell;
	rules[RULE_SUBSHELL_1].rhs[0] = SYM_LPARENTHESIS;
	rules[RULE_SUBSHELL_1].rhs[1] = SYM_compound_list;
	rules[RULE_SUBSHELL_1].rhs[2] = SYM_RPARENTHESIS;
	rules[RULE_SUBSHELL_1].rhs_len = 3;
}
