#include "context.h"
#include "quote_removal_context_.h"

static t_context_args	context_dollar_squote_rules(t_expander *expander)
{
	t_context_args	args;

	args.word = &expander->word;
	args.word_expanded = &expander->word_exp;
	args.is_end = is_context_dollar_squote_ending;
	args.is_in_whitelist = is_in_context_dollar_squote_whitelist;
	return (args);
}

t_error	context_dollar_squote(t_expander *expander)
{
	return (context_scan(expander, context_dollar_squote_rules(expander)));
}
