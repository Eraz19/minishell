#include "parser.h"

static void	parser_rules_init_function_body_1(t_rule *rules);
static void	parser_rules_init_function_body_2(t_rule *rules);

/*
function_body    : compound_command               (apply rule 9)
                 | compound_command redirect_list (apply rule 9)
                 ;
*/
void	parser_rules_init_function_body(t_rule *rules)
{
	parser_rules_init_function_body_1(rules);
	parser_rules_init_function_body_2(rules);
}

// function_body -> compound_command (apply rule 9)
static void	parser_rules_init_function_body_1(t_rule *rules)
{
	rules[RULE_FUNCTION_BODY_1].lhs = SYM_function_body;
	rules[RULE_FUNCTION_BODY_1].rhs[0] = SYM_compound_command;
	rules[RULE_FUNCTION_BODY_1].rhs_len = 1;
}

// function_body -> compound_command redirect_list (apply rule 9)
static void	parser_rules_init_function_body_2(t_rule *rules)
{
	rules[RULE_FUNCTION_BODY_2].lhs = SYM_function_body;
	rules[RULE_FUNCTION_BODY_2].rhs[0] = SYM_compound_command;
	rules[RULE_FUNCTION_BODY_2].rhs[1] = SYM_redirect_list;
	rules[RULE_FUNCTION_BODY_2].rhs_len = 2;
}
