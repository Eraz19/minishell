#include "builder.h"

static void	rules_build_case_clause_1(t_rule *rules);
static void	rules_build_case_clause_2(t_rule *rules);
static void	rules_build_case_clause_3(t_rule *rules);

/*
case_clause      : Case WORD linebreak in linebreak case_list    Esac
                 | Case WORD linebreak in linebreak case_list_ns Esac
                 | Case WORD linebreak in linebreak              Esac
                 ;
*/
void	rules_build_case_clause(t_rule *rules)
{
	rules_build_case_clause_1(rules);
	rules_build_case_clause_2(rules);
	rules_build_case_clause_3(rules);
}

// case_clause -> Case WORD linebreak in linebreak case_list Esac
static void	rules_build_case_clause_1(t_rule *rules)
{
	rules[RULE_CASE_CLAUSE_1].lhs = SYM_case_clause;
	rules[RULE_CASE_CLAUSE_1].rhs[0] = SYM_Case;
	rules[RULE_CASE_CLAUSE_1].rhs[1] = SYM_WORD;
	rules[RULE_CASE_CLAUSE_1].rhs[2] = SYM_linebreak;
	rules[RULE_CASE_CLAUSE_1].rhs[3] = SYM_in;
	rules[RULE_CASE_CLAUSE_1].rhs[4] = SYM_linebreak;
	rules[RULE_CASE_CLAUSE_1].rhs[5] = SYM_case_list;
	rules[RULE_CASE_CLAUSE_1].rhs[6] = SYM_Esac;
	rules[RULE_CASE_CLAUSE_1].rhs_len = 7;
}

// case_clause -> Case WORD linebreak in linebreak case_list_ns Esac
static void	rules_build_case_clause_2(t_rule *rules)
{
	rules[RULE_CASE_CLAUSE_2].lhs = SYM_case_clause;
	rules[RULE_CASE_CLAUSE_2].rhs[0] = SYM_Case;
	rules[RULE_CASE_CLAUSE_2].rhs[1] = SYM_WORD;
	rules[RULE_CASE_CLAUSE_2].rhs[2] = SYM_linebreak;
	rules[RULE_CASE_CLAUSE_2].rhs[3] = SYM_in;
	rules[RULE_CASE_CLAUSE_2].rhs[4] = SYM_linebreak;
	rules[RULE_CASE_CLAUSE_2].rhs[5] = SYM_case_list_ns;
	rules[RULE_CASE_CLAUSE_2].rhs[6] = SYM_Esac;
	rules[RULE_CASE_CLAUSE_2].rhs_len = 7;
}

// case_clause -> Case WORD linebreak in linebreak Esac
static void	rules_build_case_clause_3(t_rule *rules)
{
	rules[RULE_CASE_CLAUSE_3].lhs = SYM_case_clause;
	rules[RULE_CASE_CLAUSE_3].rhs[0] = SYM_Case;
	rules[RULE_CASE_CLAUSE_3].rhs[1] = SYM_WORD;
	rules[RULE_CASE_CLAUSE_3].rhs[2] = SYM_linebreak;
	rules[RULE_CASE_CLAUSE_3].rhs[3] = SYM_in;
	rules[RULE_CASE_CLAUSE_3].rhs[4] = SYM_linebreak;
	rules[RULE_CASE_CLAUSE_3].rhs[5] = SYM_Esac;
	rules[RULE_CASE_CLAUSE_3].rhs_len = 6;
}
