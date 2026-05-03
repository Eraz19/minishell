#include "parser.h"

static void	rules_build_sequential_sep_1(t_rule *rules);
static void	rules_build_sequential_sep_2(t_rule *rules);

/*
sequential_sep   : ';' linebreak
                 | newline_list
                 ;
*/
void	rules_build_sequential_sep(t_rule *rules)
{
	rules_build_sequential_sep_1(rules);
	rules_build_sequential_sep_2(rules);
}

// sequential_sep -> ';' linebreak
static void	rules_build_sequential_sep_1(t_rule *rules)
{
	rules[RULE_SEQUENTIAL_SEP_1].lhs = SYM_sequential_sep;
	rules[RULE_SEQUENTIAL_SEP_1].rhs[0] = SYM_SEMI;
	rules[RULE_SEQUENTIAL_SEP_1].rhs[1] = SYM_linebreak;
	rules[RULE_SEQUENTIAL_SEP_1].rhs_len = 2;
}

// sequential_sep -> newline_list
static void	rules_build_sequential_sep_2(t_rule *rules)
{
	rules[RULE_SEQUENTIAL_SEP_2].lhs = SYM_sequential_sep;
	rules[RULE_SEQUENTIAL_SEP_2].rhs[0] = SYM_newline_list;
	rules[RULE_SEQUENTIAL_SEP_2].rhs_len = 1;
}
