#include "parser_rules.h"
#include "libft.h"

void	parser_rules_init(t_rule *rules)
{
	ft_bzero(rules, RULE_COUNT * sizeof(*rules));
	parser_rules_init_program(rules);
}
