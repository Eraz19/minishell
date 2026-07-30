#include "rules__type.h"

/*
cmd_name         : WORD (apply rule 7a)
                 ;
*/
void	rules_build_cmd_name(t_rule *rules)
{
	rules[RULE_CMD_NAME_1].lhs = SYM_cmd_name;
	rules[RULE_CMD_NAME_1].rhs[0] = SYM_WORD;
	rules[RULE_CMD_NAME_1].rhs_len = 1;
}
