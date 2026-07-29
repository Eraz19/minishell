#ifndef GRAMMAR_RULE_STATE_H
# define GRAMMAR_RULE_STATE_H

# include "grammar_symbols.h"
# include <stddef.h>

/*
rule_state		aka item in LR parsing theory
rule_state.pos	aka item.dot in LR parsing theory
*/
typedef struct s_rule_state
{
	size_t		rule_id;
	size_t		pos;
	t_symbol	lookahead;
}	t_rule_state;

#endif
