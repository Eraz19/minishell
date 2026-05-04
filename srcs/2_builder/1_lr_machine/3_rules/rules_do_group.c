#include "parser.h"
#include "hooks.h"

/*
do_group         : Do compound_list Done (apply rule 6)
                 ;
*/
void	rules_build_do_group(t_rule *rules)
{
	rules[RULE_DO_GROUP_1].lhs = SYM_do_group;
	rules[RULE_DO_GROUP_1].rhs[0] = SYM_Do;
	rules[RULE_DO_GROUP_1].rhs[1] = SYM_compound_list;
	rules[RULE_DO_GROUP_1].rhs[2] = SYM_Done;
	rules[RULE_DO_GROUP_1].rhs_len = 3;
	rules[RULE_DO_GROUP_1].hook = hook_6;
}
