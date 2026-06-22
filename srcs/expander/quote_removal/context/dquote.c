#include "context.h"
#include "quote_removal_context_.h"

static t_context_args	context_dquote_rules(
	t_expander_word *word,
	t_expander_word *word_expanded)
{
	t_context_args	args;
	
	args.word = word;
	args.context = CONTEXT_DQUOTE;
	args.word_expanded = word_expanded;
	args.is_end = is_context_dquote_ending;
	args.is_in_whitelist = is_in_context_dquote_whitelist;
	return (args);
}

t_error	context_dquote(
	t_expander *state,
	t_expander_word *word,
	t_expander_word *word_exp)
{
	return (context_scan(state, context_dquote_rules(word, word_exp)));
}
