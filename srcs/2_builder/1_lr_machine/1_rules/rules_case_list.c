#include "parser.h"

static void	rules_init_case_list_1(t_rule *rules);
static void	rules_init_case_list_2(t_rule *rules);

/*
case_list        : case_list case_item
                 |           case_item
                 ;
*/
void	rules_init_case_list(t_rule *rules)
{
	rules_init_case_list_1(rules);
	rules_init_case_list_2(rules);
}

// case_list -> case_list case_item
static void	rules_init_case_list_1(t_rule *rules)
{
	rules[RULE_CASE_LIST_1].lhs = SYM_case_list;
	rules[RULE_CASE_LIST_1].rhs[0] = SYM_case_list;
	rules[RULE_CASE_LIST_1].rhs[1] = SYM_case_item;
	rules[RULE_CASE_LIST_1].rhs_len = 2;
}

// case_list -> case_item
static void	rules_init_case_list_2(t_rule *rules)
{
	rules[RULE_CASE_LIST_2].lhs = SYM_case_list;
	rules[RULE_CASE_LIST_2].rhs[0] = SYM_case_item;
	rules[RULE_CASE_LIST_2].rhs_len = 1;
}
