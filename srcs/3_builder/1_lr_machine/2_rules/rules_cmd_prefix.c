#include "builder.h"

static void	rules_build_cmd_prefix_1(t_rule *rules);
static void	rules_build_cmd_prefix_2(t_rule *rules);
static void	rules_build_cmd_prefix_3(t_rule *rules);
static void	rules_build_cmd_prefix_4(t_rule *rules);

/*
cmd_prefix       :            io_redirect
                 | cmd_prefix io_redirect
                 |            ASSIGNMENT_WORD
                 | cmd_prefix ASSIGNMENT_WORD
                 ;
*/
void	rules_build_cmd_prefix(t_rule *rules)
{
	rules_build_cmd_prefix_1(rules);
	rules_build_cmd_prefix_2(rules);
	rules_build_cmd_prefix_3(rules);
	rules_build_cmd_prefix_4(rules);
}

// cmd_prefix -> io_redirect
static void	rules_build_cmd_prefix_1(t_rule *rules)
{
	rules[RULE_CMD_PREFIX_1].lhs = SYM_cmd_prefix;
	rules[RULE_CMD_PREFIX_1].rhs[0] = SYM_io_redirect;
	rules[RULE_CMD_PREFIX_1].rhs_len = 1;
}

// cmd_prefix -> cmd_prefix io_redirect
static void	rules_build_cmd_prefix_2(t_rule *rules)
{
	rules[RULE_CMD_PREFIX_2].lhs = SYM_cmd_prefix;
	rules[RULE_CMD_PREFIX_2].rhs[0] = SYM_cmd_prefix;
	rules[RULE_CMD_PREFIX_2].rhs[1] = SYM_io_redirect;
	rules[RULE_CMD_PREFIX_2].rhs_len = 2;
}

// cmd_prefix -> ASSIGNMENT_WORD
static void	rules_build_cmd_prefix_3(t_rule *rules)
{
	rules[RULE_CMD_PREFIX_3].lhs = SYM_cmd_prefix;
	rules[RULE_CMD_PREFIX_3].rhs[0] = SYM_ASSIGNMENT_WORD;
	rules[RULE_CMD_PREFIX_3].rhs_len = 1;
}

// cmd_prefix -> cmd_prefix ASSIGNMENT_WORD
static void	rules_build_cmd_prefix_4(t_rule *rules)
{
	rules[RULE_CMD_PREFIX_4].lhs = SYM_cmd_prefix;
	rules[RULE_CMD_PREFIX_4].rhs[0] = SYM_cmd_prefix;
	rules[RULE_CMD_PREFIX_4].rhs[1] = SYM_ASSIGNMENT_WORD;
	rules[RULE_CMD_PREFIX_4].rhs_len = 2;
}
