#include "parser.h"
#include "parser_hooks.h"

/*
filename         : WORD (apply rule 2)
                 ;
*/
void	parser_rules_init_filename(t_rule *rules)
{
	rules[RULE_FILENAME_1].lhs = SYM_filename;
	rules[RULE_FILENAME_1].rhs[0] = SYM_WORD;
	rules[RULE_FILENAME_1].rhs_len = 1;
	rules[RULE_FILENAME_1].hook = hook_2;
}
