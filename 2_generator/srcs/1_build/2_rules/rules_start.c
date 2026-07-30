#include "generator_rules_priv.h"

void	rules_build_start_1(t_rule *rules);
void	rules_build_start_2(t_rule *rules);

/*
start            : program
                 | cmd_sub	(⚠️ Custom rule bash-like cmd sub parsing hack)
                 ;
*/
void	rules_build_start(t_rule *rules)
{
	rules_build_start_1(rules);
	rules_build_start_2(rules);
}

void	rules_build_start_1(t_rule *rules)
{
	rules[RULE_START_1].lhs = SYM_start;
	rules[RULE_START_1].rhs[0] = SYM_program;
	rules[RULE_START_1].rhs_len = 1;
}

void	rules_build_start_2(t_rule *rules)
{
	rules[RULE_START_2].lhs = SYM_start;
	rules[RULE_START_2].rhs[0] = SYM_cmd_sub;
	rules[RULE_START_2].rhs_len = 1;
}
