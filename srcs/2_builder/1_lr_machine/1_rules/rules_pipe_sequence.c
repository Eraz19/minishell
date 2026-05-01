#include "parser.h"

static void	rules_init_pipe_sequence_1(t_rule *rules);
static void	rules_init_pipe_sequence_2(t_rule *rules);

/*
pipe_sequence    :                             command
                 | pipe_sequence '|' linebreak command
                 ;
*/
void	rules_init_pipe_sequence(t_rule *rules)
{
	rules_init_pipe_sequence_1(rules);
	rules_init_pipe_sequence_2(rules);
}

// pipe_sequence -> command
static void	rules_init_pipe_sequence_1(t_rule *rules)
{
	rules[RULE_PIPE_SEQUENCE_1].lhs = SYM_pipe_sequence;
	rules[RULE_PIPE_SEQUENCE_1].rhs[0] = SYM_command;
	rules[RULE_PIPE_SEQUENCE_1].rhs_len = 1;
}

// pipe_sequence -> '|' linebreak command
static void	rules_init_pipe_sequence_2(t_rule *rules)
{
	rules[RULE_PIPE_SEQUENCE_2].lhs = SYM_pipe_sequence;
	rules[RULE_PIPE_SEQUENCE_2].rhs[0] = SYM_pipe_sequence;
	rules[RULE_PIPE_SEQUENCE_2].rhs[1] = SYM_PIPE;
	rules[RULE_PIPE_SEQUENCE_2].rhs[2] = SYM_linebreak;
	rules[RULE_PIPE_SEQUENCE_2].rhs[3] = SYM_command;
	rules[RULE_PIPE_SEQUENCE_2].rhs_len = 4;
}
