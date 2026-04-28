#include "parser_rules.h"

/*
program          : linebreak complete_commands linebreak
                 | linebreak
                 ;
*/
void	parser_rules_init_program(t_rule *rules)
{
	rules[RULE_PROGRAM_FROM_COMPLETE_COMMANDS].lhs = SYM_program;
	rules[RULE_PROGRAM_FROM_COMPLETE_COMMANDS].rhs[0] = SYM_linebreak;
	rules[RULE_PROGRAM_FROM_COMPLETE_COMMANDS].rhs[1] = SYM_complete_commands;
	rules[RULE_PROGRAM_FROM_COMPLETE_COMMANDS].rhs[2] = SYM_linebreak;
	rules[RULE_PROGRAM_FROM_COMPLETE_COMMANDS].rhs_len = 3;
	rules[RULE_PROGRAM_FROM_LINEBREAK].lhs = SYM_program;
	rules[RULE_PROGRAM_FROM_LINEBREAK].rhs[0] = SYM_linebreak;
	rules[RULE_PROGRAM_FROM_LINEBREAK].rhs_len = 1;
}
