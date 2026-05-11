#include "builder.h"
#include "hooks.h"

static void	rules_build_pattern_list_1(t_rule *rules);
static void	rules_build_pattern_list_2(t_rule *rules);
static void	rules_build_pattern_list_3(t_rule *rules);

/*
pattern_list     :                  WORD (apply rule 4)
                 |              '(' WORD (do NOT apply rule 4)
                 | pattern_list '|' WORD (do NOT apply rule 4)
                 ;
*/
void	rules_build_pattern_list(t_rule *rules)
{
	rules_build_pattern_list_1(rules);
	rules_build_pattern_list_2(rules);
	rules_build_pattern_list_3(rules);
}

// pattern_list -> WORD (apply rule 4)
static void	rules_build_pattern_list_1(t_rule *rules)
{
	rules[RULE_PATTERN_LIST_1].lhs = SYM_pattern_list;
	rules[RULE_PATTERN_LIST_1].rhs[0] = SYM_WORD;
	rules[RULE_PATTERN_LIST_1].rhs_len = 1;
	rules[RULE_PATTERN_LIST_1].hook = hook_4;
}

// pattern_list -> '(' WORD (do NOT apply rule 4)
static void	rules_build_pattern_list_2(t_rule *rules)
{
	rules[RULE_PATTERN_LIST_2].lhs = SYM_pattern_list;
	rules[RULE_PATTERN_LIST_2].rhs[0] = SYM_LPARENTHESIS;
	rules[RULE_PATTERN_LIST_2].rhs[1] = SYM_WORD;
	rules[RULE_PATTERN_LIST_2].rhs_len = 2;
}

// pattern_list -> pattern_list '|' WORD (do NOT apply rule 4)
static void	rules_build_pattern_list_3(t_rule *rules)
{
	rules[RULE_PATTERN_LIST_3].lhs = SYM_pattern_list;
	rules[RULE_PATTERN_LIST_3].rhs[0] = SYM_pattern_list;
	rules[RULE_PATTERN_LIST_3].rhs[1] = SYM_PIPE;
	rules[RULE_PATTERN_LIST_3].rhs[2] = SYM_WORD;
	rules[RULE_PATTERN_LIST_3].rhs_len = 3;
}
