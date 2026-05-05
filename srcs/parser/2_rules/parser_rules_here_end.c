#include "parser.h"
#include "parser_hooks.h"

/*
here_end         : WORD (apply rule 3)
                 ;
*/
void	parser_rules_init_here_end(t_rule *rules)
{
	rules[RULE_HERE_END_1].lhs = SYM_here_end;
	rules[RULE_HERE_END_1].rhs[0] = SYM_WORD;
	rules[RULE_HERE_END_1].rhs_len = 1;
	rules[RULE_HERE_END_1].hook = hook_3;
}
