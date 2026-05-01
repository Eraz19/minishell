#include "parser.h"

static void	rules_init_case_item_1(t_rule *rules);
static void	rules_init_case_item_2(t_rule *rules);
static void	rules_init_case_item_3(t_rule *rules);
static void	rules_init_case_item_4(t_rule *rules);

/*
case_item        : pattern_list ')' linebreak     DSEMI linebreak
                 | pattern_list ')' compound_list DSEMI linebreak
                 | pattern_list ')' linebreak     SEMI_AND linebreak
                 | pattern_list ')' compound_list SEMI_AND linebreak
                 ;
*/
void	rules_init_case_item(t_rule *rules)
{
	rules_init_case_item_1(rules);
	rules_init_case_item_2(rules);
	rules_init_case_item_3(rules);
	rules_init_case_item_4(rules);
}

// case_item -> pattern_list ')' linebreak DSEMI linebreak
static void	rules_init_case_item_1(t_rule *rules)
{
	rules[RULE_CASE_ITEM_1].lhs = SYM_case_item;
	rules[RULE_CASE_ITEM_1].rhs[0] = SYM_pattern_list;
	rules[RULE_CASE_ITEM_1].rhs[1] = SYM_RPARENTHESIS;
	rules[RULE_CASE_ITEM_1].rhs[2] = SYM_linebreak;
	rules[RULE_CASE_ITEM_1].rhs[3] = SYM_DSEMI;
	rules[RULE_CASE_ITEM_1].rhs[4] = SYM_linebreak;
	rules[RULE_CASE_ITEM_1].rhs_len = 5;
}

// case_item -> pattern_list ')' compound_list DSEMI linebreak
static void	rules_init_case_item_2(t_rule *rules)
{
	rules[RULE_CASE_ITEM_2].lhs = SYM_case_item;
	rules[RULE_CASE_ITEM_2].rhs[0] = SYM_pattern_list;
	rules[RULE_CASE_ITEM_2].rhs[1] = SYM_RPARENTHESIS;
	rules[RULE_CASE_ITEM_2].rhs[2] = SYM_compound_list;
	rules[RULE_CASE_ITEM_2].rhs[3] = SYM_DSEMI;
	rules[RULE_CASE_ITEM_2].rhs[4] = SYM_linebreak;
	rules[RULE_CASE_ITEM_2].rhs_len = 5;
}

// case_item -> pattern_list ')' linebreak SEMI_AND linebreak
static void	rules_init_case_item_3(t_rule *rules)
{
	rules[RULE_CASE_ITEM_3].lhs = SYM_case_item;
	rules[RULE_CASE_ITEM_3].rhs[0] = SYM_pattern_list;
	rules[RULE_CASE_ITEM_3].rhs[1] = SYM_RPARENTHESIS;
	rules[RULE_CASE_ITEM_3].rhs[2] = SYM_linebreak;
	rules[RULE_CASE_ITEM_3].rhs[3] = SYM_SEMI_AND;
	rules[RULE_CASE_ITEM_3].rhs[4] = SYM_linebreak;
	rules[RULE_CASE_ITEM_3].rhs_len = 5;
}

// case_item -> pattern_list ')' compound_list SEMI_AND linebreak
static void	rules_init_case_item_4(t_rule *rules)
{
	rules[RULE_CASE_ITEM_4].lhs = SYM_case_item;
	rules[RULE_CASE_ITEM_4].rhs[0] = SYM_pattern_list;
	rules[RULE_CASE_ITEM_4].rhs[1] = SYM_RPARENTHESIS;
	rules[RULE_CASE_ITEM_4].rhs[2] = SYM_compound_list;
	rules[RULE_CASE_ITEM_4].rhs[3] = SYM_SEMI_AND;
	rules[RULE_CASE_ITEM_4].rhs[4] = SYM_linebreak;
	rules[RULE_CASE_ITEM_4].rhs_len = 5;
}
