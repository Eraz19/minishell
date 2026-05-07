#include "builder.h"
#include "hooks.h"

/*
in               : In (apply rule 6)
                 ;
*/
void	rules_build_in(t_rule *rules)
{
	rules[RULE_IN_1].lhs = SYM_in;
	rules[RULE_IN_1].rhs[0] = SYM_In;
	rules[RULE_IN_1].rhs_len = 1;
	rules[RULE_IN_1].hook = hook_6;
}
