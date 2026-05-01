#include "parser.h"
#include "hooks.h"

/*
filename         : WORD (apply rule 2)
                 ;
*/
void	rules_init_filename(t_rule *rules)
{
	rules[RULE_FILENAME_1].lhs = SYM_filename;
	rules[RULE_FILENAME_1].rhs[0] = SYM_WORD;
	rules[RULE_FILENAME_1].rhs_len = 1;
	rules[RULE_FILENAME_1].hook = hook_2;
}
