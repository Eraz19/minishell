#include "builder.h"

/*
function_definition : fname '(' ')' linebreak function_body
                    ;
*/
void	rules_build_function_definition(t_rule *rules)
{
	rules[RULE_FUNCTION_DEFINITION_1].lhs = SYM_function_definition;
	rules[RULE_FUNCTION_DEFINITION_1].rhs[0] = SYM_fname;
	rules[RULE_FUNCTION_DEFINITION_1].rhs[1] = SYM_LPARENTHESIS;
	rules[RULE_FUNCTION_DEFINITION_1].rhs[2] = SYM_RPARENTHESIS;
	rules[RULE_FUNCTION_DEFINITION_1].rhs[3] = SYM_linebreak;
	rules[RULE_FUNCTION_DEFINITION_1].rhs[4] = SYM_function_body;
	rules[RULE_FUNCTION_DEFINITION_1].rhs_len = 5;
}
