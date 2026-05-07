#include "builder.h"

static void	rules_build_io_redirect_1(t_rule *rules);
static void	rules_build_io_redirect_2(t_rule *rules);
static void	rules_build_io_redirect_3(t_rule *rules);
static void	rules_build_io_redirect_4(t_rule *rules);

/*
io_redirect      :             io_file
                 | IO_NUMBER   io_file
                 | IO_LOCATION io_file (optionally supported)
                 |             io_here
                 | IO_NUMBER   io_here
                 | IO_LOCATION io_here (optionally supported)
                 ;
*/
void	rules_build_io_redirect(t_rule *rules)
{
	rules_build_io_redirect_1(rules);
	rules_build_io_redirect_2(rules);
	rules_build_io_redirect_3(rules);
	rules_build_io_redirect_4(rules);
}

// io_redirect -> io_file
// io_redirect -> IO_NUMBER io_file
static void	rules_build_io_redirect_1(t_rule *rules)
{
	rules[RULE_IO_REDIRECT_1].lhs = SYM_io_redirect;
	rules[RULE_IO_REDIRECT_1].rhs[0] = SYM_io_file;
	rules[RULE_IO_REDIRECT_1].rhs_len = 1;
	rules[RULE_IO_REDIRECT_2].lhs = SYM_io_redirect;
	rules[RULE_IO_REDIRECT_2].rhs[0] = SYM_IO_NUMBER;
	rules[RULE_IO_REDIRECT_2].rhs[1] = SYM_io_file;
	rules[RULE_IO_REDIRECT_2].rhs_len = 2;
}

// io_redirect -> IO_LOCATION io_file (optionally supported)
// io_redirect -> io_here
static void	rules_build_io_redirect_2(t_rule *rules)
{
	rules[RULE_IO_REDIRECT_3].lhs = SYM_io_redirect;
	rules[RULE_IO_REDIRECT_3].rhs[0] = SYM_IO_LOCATION;
	rules[RULE_IO_REDIRECT_3].rhs[1] = SYM_io_file;
	rules[RULE_IO_REDIRECT_3].rhs_len = 2;
	rules[RULE_IO_REDIRECT_4].lhs = SYM_io_redirect;
	rules[RULE_IO_REDIRECT_4].rhs[0] = SYM_io_here;
	rules[RULE_IO_REDIRECT_4].rhs_len = 1;
}

// io_redirect -> IO_NUMBER io_here
static void	rules_build_io_redirect_3(t_rule *rules)
{
	rules[RULE_IO_REDIRECT_5].lhs = SYM_io_redirect;
	rules[RULE_IO_REDIRECT_5].rhs[0] = SYM_IO_NUMBER;
	rules[RULE_IO_REDIRECT_5].rhs[1] = SYM_io_here;
	rules[RULE_IO_REDIRECT_5].rhs_len = 2;
}

// io_redirect -> IO_LOCATION io_here (optionally supported)
static void	rules_build_io_redirect_4(t_rule *rules)
{
	rules[RULE_IO_REDIRECT_6].lhs = SYM_io_redirect;
	rules[RULE_IO_REDIRECT_6].rhs[0] = SYM_IO_LOCATION;
	rules[RULE_IO_REDIRECT_6].rhs[1] = SYM_io_here;
	rules[RULE_IO_REDIRECT_6].rhs_len = 2;
}
