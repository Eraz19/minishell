#include "context.h"
#include "quote_removal_context_.h"

static t_context_args	context_dquote_rules(t_expander *expander)
{
	t_context_args	args;
	
	args.word = &expander->word;
	args.context = CONTEXT_DQUOTE;
	args.word_expanded = &expander->word_exp;
	args.is_end = is_context_dquote_ending;
	args.is_in_whitelist = is_in_context_dquote_whitelist;
	return (args);
}

t_error	context_dquote(t_expander *expander)
{
	return (context_scan(expander, context_dquote_rules(expander)));
}
