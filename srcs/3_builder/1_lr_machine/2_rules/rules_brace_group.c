#include "builder.h"

/*
brace_group      : Lbrace compound_list Rbrace
                 ;
*/
void	rules_build_brace_group(t_rule *rules)
{
	rules[RULE_BRACE_GROUP_1].lhs = SYM_brace_group;
	rules[RULE_BRACE_GROUP_1].rhs[0] = SYM_Lbrace;
	rules[RULE_BRACE_GROUP_1].rhs[1] = SYM_compound_list;
	rules[RULE_BRACE_GROUP_1].rhs[2] = SYM_Rbrace;
	rules[RULE_BRACE_GROUP_1].rhs_len = 3;
}
