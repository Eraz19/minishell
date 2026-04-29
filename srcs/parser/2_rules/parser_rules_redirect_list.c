#include "parser.h"

static void	parser_rules_init_redirect_list_1(t_rule *rules);
static void	parser_rules_init_redirect_list_2(t_rule *rules);

/*
redirect_list    :               io_redirect
                 | redirect_list io_redirect
                 ;
*/
void	parser_rules_init_redirect_list(t_rule *rules)
{
	parser_rules_init_redirect_list_1(rules);
	parser_rules_init_redirect_list_2(rules);
}

// redirect_list -> io_redirect
static void	parser_rules_init_redirect_list_1(t_rule *rules)
{
	rules[RULE_REDIRECT_LIST_1].lhs = SYM_redirect_list;
	rules[RULE_REDIRECT_LIST_1].rhs[0] = SYM_io_redirect;
	rules[RULE_REDIRECT_LIST_1].rhs_len = 1;
}

// redirect_list -> redirect_list io_redirect
static void	parser_rules_init_redirect_list_2(t_rule *rules)
{
	rules[RULE_REDIRECT_LIST_2].lhs = SYM_redirect_list;
	rules[RULE_REDIRECT_LIST_2].rhs[0] = SYM_redirect_list;
	rules[RULE_REDIRECT_LIST_2].rhs[1] = SYM_io_redirect;
	rules[RULE_REDIRECT_LIST_2].rhs_len = 2;
}
