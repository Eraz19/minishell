#include "parser.h"

static void	parser_rules_init_pipeline_1(t_rule *rules);
static void	parser_rules_init_pipeline_2(t_rule *rules);

/*
pipeline         :      pipe_sequence
                 | Bang pipe_sequence
                 ;
*/
void	parser_rules_init_pipeline(t_rule *rules)
{
	parser_rules_init_pipeline_1(rules);
	parser_rules_init_pipeline_2(rules);
}

// pipeline -> pipe_sequence
static void	parser_rules_init_pipeline_1(t_rule *rules)
{
	rules[RULE_PIPELINE_1].lhs = SYM_pipeline;
	rules[RULE_PIPELINE_1].rhs[0] = SYM_pipe_sequence;
	rules[RULE_PIPELINE_1].rhs_len = 1;
}

// pipeline -> Bang pipe_sequence
static void	parser_rules_init_pipeline_2(t_rule *rules)
{
	rules[RULE_PIPELINE_2].lhs = SYM_pipeline;
	rules[RULE_PIPELINE_2].rhs[0] = SYM_Bang;
	rules[RULE_PIPELINE_2].rhs[1] = SYM_pipe_sequence;
	rules[RULE_PIPELINE_2].rhs_len = 2;
}
