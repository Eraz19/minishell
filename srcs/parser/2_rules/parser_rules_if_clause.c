#include "parser.h"

static void	parser_rules_init_if_clause_1(t_rule *rules);
static void	parser_rules_init_if_clause_2(t_rule *rules);

/*
if_clause        : If compound_list Then compound_list else_part Fi
                 | If compound_list Then compound_list           Fi
                 ;
*/
void	parser_rules_init_if_clause(t_rule *rules)
{
	parser_rules_init_if_clause_1(rules);
	parser_rules_init_if_clause_2(rules);
}

// if_clause -> If compound_list Then compound_list else_part Fi
static void	parser_rules_init_if_clause_1(t_rule *rules)
{
	rules[RULE_IF_CLAUSE_1].lhs = SYM_if_clause;
	rules[RULE_IF_CLAUSE_1].rhs[0] = SYM_If;
	rules[RULE_IF_CLAUSE_1].rhs[1] = SYM_compound_list;
	rules[RULE_IF_CLAUSE_1].rhs[2] = SYM_Then;
	rules[RULE_IF_CLAUSE_1].rhs[3] = SYM_compound_list;
	rules[RULE_IF_CLAUSE_1].rhs[4] = SYM_else_part;
	rules[RULE_IF_CLAUSE_1].rhs[5] = SYM_Fi;
	rules[RULE_IF_CLAUSE_1].rhs_len = 6;
}

// if_clause -> If compound_list Then compound_list Fi
static void	parser_rules_init_if_clause_2(t_rule *rules)
{
	rules[RULE_IF_CLAUSE_2].lhs = SYM_if_clause;
	rules[RULE_IF_CLAUSE_2].rhs[0] = SYM_If;
	rules[RULE_IF_CLAUSE_2].rhs[1] = SYM_compound_list;
	rules[RULE_IF_CLAUSE_2].rhs[2] = SYM_Then;
	rules[RULE_IF_CLAUSE_2].rhs[3] = SYM_compound_list;
	rules[RULE_IF_CLAUSE_2].rhs[4] = SYM_Fi;
	rules[RULE_IF_CLAUSE_2].rhs_len = 5;
}
