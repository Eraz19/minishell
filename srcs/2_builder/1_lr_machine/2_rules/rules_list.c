#include "parser.h"

static void	rules_init_list_1(t_rule *rules);
static void	rules_init_list_2(t_rule *rules);

/*
list             : list separator_op and_or
                 |                   and_or
                 ;
*/
void	rules_init_list(t_rule *rules)
{
	rules_init_list_1(rules);
	rules_init_list_2(rules);
}

// list -> list separator_op and_or
static void	rules_init_list_1(t_rule *rules)
{
	rules[RULE_LIST_1].lhs = SYM_list;
	rules[RULE_LIST_1].rhs[0] = SYM_list;
	rules[RULE_LIST_1].rhs[1] = SYM_separator_op;
	rules[RULE_LIST_1].rhs[2] = SYM_and_or;
	rules[RULE_LIST_1].rhs_len = 3;
}

// list -> and_or
static void	rules_init_list_2(t_rule *rules)
{
	rules[RULE_LIST_2].lhs = SYM_list;
	rules[RULE_LIST_2].rhs[0] = SYM_and_or;
	rules[RULE_LIST_2].rhs_len = 1;
}
