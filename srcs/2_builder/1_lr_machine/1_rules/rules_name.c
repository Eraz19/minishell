#include "parser.h"
#include "hooks.h"

/*
name             : NAME (apply rule 5)
                 ;
*/
void	rules_init_name(t_rule *rules)
{
	rules[RULE_NAME_1].lhs = SYM_name;
	rules[RULE_NAME_1].rhs[0] = SYM_NAME;
	rules[RULE_NAME_1].rhs_len = 1;
	rules[RULE_NAME_1].hook = hook_5;
}
