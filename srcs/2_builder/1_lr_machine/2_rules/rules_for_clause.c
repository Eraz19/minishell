#include "parser.h"

static void	rules_build_for_clause_1(t_rule *rules);
static void	rules_build_for_clause_2(t_rule *rules);
static void	rules_build_for_clause_3(t_rule *rules);
static void	rules_build_for_clause_4(t_rule *rules);

/*
for_clause       : For name                                      do_group
                 | For name                       sequential_sep do_group
                 | For name linebreak in          sequential_sep do_group
                 | For name linebreak in wordlist sequential_sep do_group
                 ;
*/
void	rules_build_for_clause(t_rule *rules)
{
	rules_build_for_clause_1(rules);
	rules_build_for_clause_2(rules);
	rules_build_for_clause_3(rules);
	rules_build_for_clause_4(rules);
}

// for_clause -> For name do_group
static void	rules_build_for_clause_1(t_rule *rules)
{
	rules[RULE_FOR_CLAUSE_1].lhs = SYM_for_clause;
	rules[RULE_FOR_CLAUSE_1].rhs[0] = SYM_For;
	rules[RULE_FOR_CLAUSE_1].rhs[1] = SYM_name;
	rules[RULE_FOR_CLAUSE_1].rhs[2] = SYM_do_group;
	rules[RULE_FOR_CLAUSE_1].rhs_len = 3;
}

// for_clause -> For name sequential_sep do_group
static void	rules_build_for_clause_2(t_rule *rules)
{
	rules[RULE_FOR_CLAUSE_2].lhs = SYM_for_clause;
	rules[RULE_FOR_CLAUSE_2].rhs[0] = SYM_For;
	rules[RULE_FOR_CLAUSE_2].rhs[1] = SYM_name;
	rules[RULE_FOR_CLAUSE_2].rhs[2] = SYM_sequential_sep;
	rules[RULE_FOR_CLAUSE_2].rhs[3] = SYM_do_group;
	rules[RULE_FOR_CLAUSE_2].rhs_len = 4;
}

// for_clause -> For name linebreak in sequential_sep do_group
static void	rules_build_for_clause_3(t_rule *rules)
{
	rules[RULE_FOR_CLAUSE_3].lhs = SYM_for_clause;
	rules[RULE_FOR_CLAUSE_3].rhs[0] = SYM_For;
	rules[RULE_FOR_CLAUSE_3].rhs[1] = SYM_name;
	rules[RULE_FOR_CLAUSE_3].rhs[2] = SYM_linebreak;
	rules[RULE_FOR_CLAUSE_3].rhs[3] = SYM_in;
	rules[RULE_FOR_CLAUSE_3].rhs[4] = SYM_sequential_sep;
	rules[RULE_FOR_CLAUSE_3].rhs[5] = SYM_do_group;
	rules[RULE_FOR_CLAUSE_3].rhs_len = 6;
}

// for_clause -> For name linebreak in wordlist sequential_sep do_group
static void	rules_build_for_clause_4(t_rule *rules)
{
	rules[RULE_FOR_CLAUSE_4].lhs = SYM_for_clause;
	rules[RULE_FOR_CLAUSE_4].rhs[0] = SYM_For;
	rules[RULE_FOR_CLAUSE_4].rhs[1] = SYM_name;
	rules[RULE_FOR_CLAUSE_4].rhs[2] = SYM_linebreak;
	rules[RULE_FOR_CLAUSE_4].rhs[3] = SYM_in;
	rules[RULE_FOR_CLAUSE_4].rhs[4] = SYM_wordlist;
	rules[RULE_FOR_CLAUSE_4].rhs[5] = SYM_sequential_sep;
	rules[RULE_FOR_CLAUSE_4].rhs[6] = SYM_do_group;
	rules[RULE_FOR_CLAUSE_4].rhs_len = 7;
}
