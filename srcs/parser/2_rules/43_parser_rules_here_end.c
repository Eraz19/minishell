#include "parser.h"

/*
here_end         : WORD (apply rule 3 + trigger lexer here_doc_mode after NEWLINE)
                 ;
*/
void	parser_rules_init_here_end(t_rule *rules)
{
	rules[RULE_HERE_END_1].lhs = SYM_here_end;
	rules[RULE_HERE_END_1].rhs[0] = SYM_WORD;
	rules[RULE_HERE_END_1].rhs_len = 1;
}
