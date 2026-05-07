#include "builder.h"

static void	rules_build_newline_list_1(t_rule *rules);
static void	rules_build_newline_list_2(t_rule *rules);

/*
newline_list     :              NEWLINE
                 | newline_list NEWLINE
                 ;
*/
void	rules_build_newline_list(t_rule *rules)
{
	rules_build_newline_list_1(rules);
	rules_build_newline_list_2(rules);
}

// newline_list -> NEWLINE
static void	rules_build_newline_list_1(t_rule *rules)
{
	rules[RULE_NEWLINE_LIST_1].lhs = SYM_newline_list;
	rules[RULE_NEWLINE_LIST_1].rhs[0] = SYM_NEWLINE;
	rules[RULE_NEWLINE_LIST_1].rhs_len = 1;
}

// newline_list -> newline_list NEWLINE
static void	rules_build_newline_list_2(t_rule *rules)
{
	rules[RULE_NEWLINE_LIST_2].lhs = SYM_newline_list;
	rules[RULE_NEWLINE_LIST_2].rhs[0] = SYM_newline_list;
	rules[RULE_NEWLINE_LIST_2].rhs[1] = SYM_NEWLINE;
	rules[RULE_NEWLINE_LIST_2].rhs_len = 2;
}
