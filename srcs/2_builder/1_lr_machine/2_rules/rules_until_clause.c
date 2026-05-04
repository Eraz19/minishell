#include "parser.h"

/*
until_clause     : Until compound_list do_group
                 ;
*/
void	rules_build_until_clause(t_rule *rules)
{
	rules[RULE_UNTIL_CLAUSE_1].lhs = SYM_until_clause;
	rules[RULE_UNTIL_CLAUSE_1].rhs[0] = SYM_Until;
	rules[RULE_UNTIL_CLAUSE_1].rhs[1] = SYM_compound_list;
	rules[RULE_UNTIL_CLAUSE_1].rhs[2] = SYM_do_group;
	rules[RULE_UNTIL_CLAUSE_1].rhs_len = 3;
}
