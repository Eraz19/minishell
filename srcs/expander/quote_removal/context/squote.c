#include "context.h"
#include "quote_removal_context_.h"

static t_context_args	context_squote_rules(t_expander *expander)
{
	t_context_args	args;
	
	args.word = &expander->word;
	args.context = CONTEXT_SQUOTE;
	args.is_in_whitelist = NULL;
	args.word_expanded = &expander->word_exp;
	args.is_end = is_context_squote_ending;
	return (args);
}

t_error	context_squote(t_expander *expander)
{
	return (context_scan(expander, context_squote_rules(expander)));
}
