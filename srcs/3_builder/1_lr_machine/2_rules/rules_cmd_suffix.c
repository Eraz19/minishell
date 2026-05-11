#include "builder.h"

static void	rules_build_cmd_suffix_1(t_rule *rules);
static void	rules_build_cmd_suffix_2(t_rule *rules);
static void	rules_build_cmd_suffix_3(t_rule *rules);
static void	rules_build_cmd_suffix_4(t_rule *rules);

/*
cmd_suffix       :            io_redirect
                 | cmd_suffix io_redirect
                 |            WORD
                 | cmd_suffix WORD
                 ;
*/
void	rules_build_cmd_suffix(t_rule *rules)
{
	rules_build_cmd_suffix_1(rules);
	rules_build_cmd_suffix_2(rules);
	rules_build_cmd_suffix_3(rules);
	rules_build_cmd_suffix_4(rules);
}

// cmd_suffix -> io_redirect
static void	rules_build_cmd_suffix_1(t_rule *rules)
{
	rules[RULE_CMD_SUFFIX_1].lhs = SYM_cmd_suffix;
	rules[RULE_CMD_SUFFIX_1].rhs[0] = SYM_io_redirect;
	rules[RULE_CMD_SUFFIX_1].rhs_len = 1;
}

// cmd_suffix -> cmd_suffix io_redirect
static void	rules_build_cmd_suffix_2(t_rule *rules)
{
	rules[RULE_CMD_SUFFIX_2].lhs = SYM_cmd_suffix;
	rules[RULE_CMD_SUFFIX_2].rhs[0] = SYM_cmd_suffix;
	rules[RULE_CMD_SUFFIX_2].rhs[1] = SYM_io_redirect;
	rules[RULE_CMD_SUFFIX_2].rhs_len = 2;
}

// cmd_suffix -> WORD
static void	rules_build_cmd_suffix_3(t_rule *rules)
{
	rules[RULE_CMD_SUFFIX_3].lhs = SYM_cmd_suffix;
	rules[RULE_CMD_SUFFIX_3].rhs[0] = SYM_WORD;
	rules[RULE_CMD_SUFFIX_3].rhs_len = 1;
}

// cmd_suffix -> cmd_suffix WORD
static void	rules_build_cmd_suffix_4(t_rule *rules)
{
	rules[RULE_CMD_SUFFIX_4].lhs = SYM_cmd_suffix;
	rules[RULE_CMD_SUFFIX_4].rhs[0] = SYM_cmd_suffix;
	rules[RULE_CMD_SUFFIX_4].rhs[1] = SYM_WORD;
	rules[RULE_CMD_SUFFIX_4].rhs_len = 2;
}
