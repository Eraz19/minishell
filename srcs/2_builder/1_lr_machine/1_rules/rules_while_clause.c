#include "parser.h"

/*
while_clause     : While compound_list do_group
                 ;
*/
void	rules_init_while_clause(t_rule *rules)
{
	rules[RULE_WHILE_CLAUSE_1].lhs = SYM_while_clause;
	rules[RULE_WHILE_CLAUSE_1].rhs[0] = SYM_While;
	rules[RULE_WHILE_CLAUSE_1].rhs[1] = SYM_compound_list;
	rules[RULE_WHILE_CLAUSE_1].rhs[2] = SYM_do_group;
	rules[RULE_WHILE_CLAUSE_1].rhs_len = 3;
}
