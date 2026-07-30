#include "generator_rules_priv.h"

/*
⚠️ Custom rule (bash-like cmd sub parsing hack)
cmd_sub          : DOLPAREN compound_list ')'
                 ;
*/
void	rules_build_cmd_sub(t_rule *rules)
{
	rules[RULE_CMD_SUB].lhs = SYM_cmd_sub;
	rules[RULE_CMD_SUB].rhs[0] = SYM_DOLPAREN;
	rules[RULE_CMD_SUB].rhs[1] = SYM_compound_list;
	rules[RULE_CMD_SUB].rhs[2] = SYM_RPARENTHESIS;
	rules[RULE_CMD_SUB].rhs_len = 3;
}
