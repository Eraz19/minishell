#include "parser.h"

static void	parser_rules_init_else_part_1(t_rule *rules);
static void	parser_rules_init_else_part_2(t_rule *rules);
static void	parser_rules_init_else_part_3(t_rule *rules);

/*
else_part        : Elif compound_list Then compound_list
                 | Elif compound_list Then compound_list else_part
                 | Else compound_list
                 ;
*/
void	parser_rules_init_else_part(t_rule *rules)
{
	parser_rules_init_else_part_1(rules);
	parser_rules_init_else_part_2(rules);
	parser_rules_init_else_part_3(rules);
}

// else_part -> Elif compound_list Then compound_list
static void	parser_rules_init_else_part_1(t_rule *rules)
{
	rules[RULE_ELSE_PART_1].lhs = SYM_else_part;
	rules[RULE_ELSE_PART_1].rhs[0] = SYM_Elif;
	rules[RULE_ELSE_PART_1].rhs[1] = SYM_compound_list;
	rules[RULE_ELSE_PART_1].rhs[2] = SYM_Then;
	rules[RULE_ELSE_PART_1].rhs[3] = SYM_compound_list;
	rules[RULE_ELSE_PART_1].rhs_len = 4;
}

// else_part -> Elif compound_list Then compound_list else_part
static void	parser_rules_init_else_part_2(t_rule *rules)
{
	rules[RULE_ELSE_PART_2].lhs = SYM_else_part;
	rules[RULE_ELSE_PART_2].rhs[0] = SYM_Elif;
	rules[RULE_ELSE_PART_2].rhs[1] = SYM_compound_list;
	rules[RULE_ELSE_PART_2].rhs[2] = SYM_Then;
	rules[RULE_ELSE_PART_2].rhs[3] = SYM_compound_list;
	rules[RULE_ELSE_PART_2].rhs[4] = SYM_else_part;
	rules[RULE_ELSE_PART_2].rhs_len = 5;
}

// else_part -> Else compound_list
static void	parser_rules_init_else_part_3(t_rule *rules)
{
	rules[RULE_ELSE_PART_3].lhs = SYM_else_part;
	rules[RULE_ELSE_PART_3].rhs[0] = SYM_Else;
	rules[RULE_ELSE_PART_3].rhs[1] = SYM_compound_list;
	rules[RULE_ELSE_PART_3].rhs_len = 2;
}
