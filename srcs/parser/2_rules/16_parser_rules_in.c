#include "parser.h"

/*
in               : In (apply rule 6)
                 ;
*/
void	parser_rules_init_in(t_rule *rules)
{
	rules[RULE_IN_1].lhs = SYM_in;
	rules[RULE_IN_1].rhs[0] = SYM_In;
	rules[RULE_IN_1].rhs_len = 1;
}
