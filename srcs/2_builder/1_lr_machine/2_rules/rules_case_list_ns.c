#include "builder.h"

static void	rules_build_case_list_ns_1(t_rule *rules);
static void	rules_build_case_list_ns_2(t_rule *rules);

/*
case_list_ns     : case_list case_item_ns
                 |           case_item_ns
                 ;
*/
void	rules_build_case_list_ns(t_rule *rules)
{
	rules_build_case_list_ns_1(rules);
	rules_build_case_list_ns_2(rules);
}

// case_list_ns -> case_list case_item_ns
static void	rules_build_case_list_ns_1(t_rule *rules)
{
	rules[RULE_CASE_LIST_NS_1].lhs = SYM_case_list_ns;
	rules[RULE_CASE_LIST_NS_1].rhs[0] = SYM_case_list;
	rules[RULE_CASE_LIST_NS_1].rhs[1] = SYM_case_item_ns;
	rules[RULE_CASE_LIST_NS_1].rhs_len = 2;
}

// case_list_ns -> case_item_ns
static void	rules_build_case_list_ns_2(t_rule *rules)
{
	rules[RULE_CASE_LIST_NS_2].lhs = SYM_case_list_ns;
	rules[RULE_CASE_LIST_NS_2].rhs[0] = SYM_case_item_ns;
	rules[RULE_CASE_LIST_NS_2].rhs_len = 1;
}
