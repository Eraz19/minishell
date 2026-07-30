#include "rules__type.h"

/*
cmd_word         : WORD (apply rule 7b)
                 ;
*/
void	rules_build_cmd_word(t_rule *rules)
{
	rules[RULE_CMD_WORD_1].lhs = SYM_cmd_word;
	rules[RULE_CMD_WORD_1].rhs[0] = SYM_WORD;
	rules[RULE_CMD_WORD_1].rhs_len = 1;
}
