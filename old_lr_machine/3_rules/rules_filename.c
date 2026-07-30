#include "rules__type.h"

/*
filename         : WORD (apply rule 2)
                 ;
*/
void	rules_build_filename(t_rule *rules)
{
	rules[RULE_FILENAME_1].lhs = SYM_filename;
	rules[RULE_FILENAME_1].rhs[0] = SYM_WORD;
	rules[RULE_FILENAME_1].rhs_len = 1;
}
