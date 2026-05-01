#include "parser.h"

static void	rules_init_and_or_1(t_rule *rules);
static void	rules_init_and_or_2(t_rule *rules);
static void	rules_init_and_or_3(t_rule *rules);

/*
and_or           :                         pipeline
                 | and_or AND_IF linebreak pipeline
                 | and_or OR_IF  linebreak pipeline
                 ;
*/
void	rules_init_and_or(t_rule *rules)
{
	rules_init_and_or_1(rules);
	rules_init_and_or_2(rules);
	rules_init_and_or_3(rules);
}

// and_or -> pipeline
static void	rules_init_and_or_1(t_rule *rules)
{
	rules[RULE_AND_OR_1].lhs = SYM_and_or;
	rules[RULE_AND_OR_1].rhs[0] = SYM_pipeline;
	rules[RULE_AND_OR_1].rhs_len = 1;
}

// and_or -> and_or AND_IF linebreak pipeline
static void	rules_init_and_or_2(t_rule *rules)
{
	rules[RULE_AND_OR_2].lhs = SYM_and_or;
	rules[RULE_AND_OR_2].rhs[0] = SYM_and_or;
	rules[RULE_AND_OR_2].rhs[1] = SYM_AND_IF;
	rules[RULE_AND_OR_2].rhs[2] = SYM_linebreak;
	rules[RULE_AND_OR_2].rhs[3] = SYM_pipeline;
	rules[RULE_AND_OR_2].rhs_len = 4;
}

// and_or -> and_or OR_IF linebreak pipeline
static void	rules_init_and_or_3(t_rule *rules)
{
	rules[RULE_AND_OR_3].lhs = SYM_and_or;
	rules[RULE_AND_OR_3].rhs[0] = SYM_and_or;
	rules[RULE_AND_OR_3].rhs[1] = SYM_OR_IF;
	rules[RULE_AND_OR_3].rhs[2] = SYM_linebreak;
	rules[RULE_AND_OR_3].rhs[3] = SYM_pipeline;
	rules[RULE_AND_OR_3].rhs_len = 4;
}
