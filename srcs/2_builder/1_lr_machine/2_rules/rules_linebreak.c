#include "parser.h"

static void	rules_build_linebreak_1(t_rule *rules);
static void	rules_build_linebreak_2(t_rule *rules);

/*
linebreak        : newline_list
                 | <empty>
                 ;
*/
void	rules_build_linebreak(t_rule *rules)
{
	rules_build_linebreak_1(rules);
	rules_build_linebreak_2(rules);
}

// linebreak -> newline_list
static void	rules_build_linebreak_1(t_rule *rules)
{
	rules[RULE_LINEBREAK_1].lhs = SYM_linebreak;
	rules[RULE_LINEBREAK_1].rhs[0] = SYM_newline_list;
	rules[RULE_LINEBREAK_1].rhs_len = 1;
}

// linebreak -> <empty>
static void	rules_build_linebreak_2(t_rule *rules)
{
	rules[RULE_LINEBREAK_2].lhs = SYM_linebreak;
	rules[RULE_LINEBREAK_2].rhs_len = 0;
}
