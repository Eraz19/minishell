#include "context.h"
#include "quote_removal_context_.h"

static t_context_args	context_squote_rules(
	t_expander_word *word,
	t_expander_word *word_expanded)
{
	t_context_args	args;
	
	args.word = word;
	args.context = SQUOTE;
	args.is_in_whitelist = NULL;
	args.word_expanded = word_expanded;
	args.is_end = is_context_squote_ending;
	return (args);
}

t_error	context_squote(
	t_expander *state,
	t_expander_word *word,
	t_expander_word *word_exp)
{
	return (context_scan(state, context_squote_rules(word, word_exp)));
}
