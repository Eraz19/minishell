#include "parser.h"

static void	rules_build_program_1(t_rule *rules);
static void	rules_build_program_2(t_rule *rules);

/*
program          : linebreak complete_commands linebreak
                 | linebreak
                 ;
*/
void	rules_build_program(t_rule *rules)
{
	rules_build_program_1(rules);
	rules_build_program_2(rules);
}

// program -> linebreak complete_commands linebreak
static void	rules_build_program_1(t_rule *rules)
{
	rules[RULE_PROGRAM_1].lhs = SYM_program;
	rules[RULE_PROGRAM_1].rhs[0] = SYM_linebreak;
	rules[RULE_PROGRAM_1].rhs[1] = SYM_complete_commands;
	rules[RULE_PROGRAM_1].rhs[2] = SYM_linebreak;
	rules[RULE_PROGRAM_1].rhs_len = 3;
}

// program -> linebreak
static void	rules_build_program_2(t_rule *rules)
{
	rules[RULE_PROGRAM_2].lhs = SYM_program;
	rules[RULE_PROGRAM_2].rhs[0] = SYM_linebreak;
	rules[RULE_PROGRAM_2].rhs_len = 1;
}
