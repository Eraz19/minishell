#include "parser.h"

static void	rules_init_io_here_1(t_rule *rules);
static void	rules_init_io_here_2(t_rule *rules);

/*
io_here          : DLESS here_end
                 | DLESSDASH here_end
                 ;
*/
void	rules_init_io_here(t_rule *rules)
{
	rules_init_io_here_1(rules);
	rules_init_io_here_2(rules);
}

// io_here -> DLESS here_end
static void	rules_init_io_here_1(t_rule *rules)
{
	rules[RULE_IO_HERE_1].lhs = SYM_io_here;
	rules[RULE_IO_HERE_1].rhs[0] = SYM_DLESS;
	rules[RULE_IO_HERE_1].rhs[1] = SYM_here_end;
	rules[RULE_IO_HERE_1].rhs_len = 2;
}

// io_here -> DLESSDASH here_end
static void	rules_init_io_here_2(t_rule *rules)
{
	rules[RULE_IO_HERE_2].lhs = SYM_io_here;
	rules[RULE_IO_HERE_2].rhs[0] = SYM_DLESSDASH;
	rules[RULE_IO_HERE_2].rhs[1] = SYM_here_end;
	rules[RULE_IO_HERE_2].rhs_len = 2;
}
