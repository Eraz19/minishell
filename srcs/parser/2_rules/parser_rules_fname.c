#include "parser.h"
#include "parser_hooks.h"

/*
fname            : NAME (apply rule 8)
                 ;
*/
void	parser_rules_init_fname(t_rule *rules)
{
	rules[RULE_FNAME_1].lhs = SYM_fname;
	rules[RULE_FNAME_1].rhs[0] = SYM_NAME;
	rules[RULE_FNAME_1].rhs_len = 1;
	rules[RULE_FNAME_1].hook = hook_8;
}
