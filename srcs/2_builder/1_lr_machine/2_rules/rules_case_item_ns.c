#include "builder.h"

static void	rules_build_case_item_ns_1(t_rule *rules);
static void	rules_build_case_item_ns_2(t_rule *rules);

/*
case_item_ns     : pattern_list ')' linebreak
                 | pattern_list ')' compound_list
                 ;
*/
void	rules_build_case_item_ns(t_rule *rules)
{
	rules_build_case_item_ns_1(rules);
	rules_build_case_item_ns_2(rules);
}

// case_item_ns -> pattern_list ')' linebreak
static void	rules_build_case_item_ns_1(t_rule *rules)
{
	rules[RULE_CASE_ITEM_NS_1].lhs = SYM_case_item_ns;
	rules[RULE_CASE_ITEM_NS_1].rhs[0] = SYM_pattern_list;
	rules[RULE_CASE_ITEM_NS_1].rhs[1] = SYM_RPARENTHESIS;
	rules[RULE_CASE_ITEM_NS_1].rhs[2] = SYM_linebreak;
	rules[RULE_CASE_ITEM_NS_1].rhs_len = 3;
}

// case_item_ns -> pattern_list ')' compound_list
static void	rules_build_case_item_ns_2(t_rule *rules)
{
	rules[RULE_CASE_ITEM_NS_2].lhs = SYM_case_item_ns;
	rules[RULE_CASE_ITEM_NS_2].rhs[0] = SYM_pattern_list;
	rules[RULE_CASE_ITEM_NS_2].rhs[1] = SYM_RPARENTHESIS;
	rules[RULE_CASE_ITEM_NS_2].rhs[2] = SYM_compound_list;
	rules[RULE_CASE_ITEM_NS_2].rhs_len = 3;
}
