#include "parser.h"

/*
start            : program
                 ;
*/
void	rules_build_start(t_rule *rules)
{
	rules[RULE_START_1].lhs = SYM_start;
	rules[RULE_START_1].rhs[0] = SYM_program;
	rules[RULE_START_1].rhs_len = 1;
}
