#include "context.h"
#include "quote_removal_context_.h"

static t_context_args	context_dollar_squote_rules(
	t_expander_word *word,
	t_expander_word *word_expanded)
{
	t_context_args	args;

	args.word = word;
	args.context = DOLLAR_SQUOTE;
	args.word_expanded = word_expanded;
	args.is_end = is_context_dollar_squote_ending;
	args.is_in_whitelist = is_in_context_dollar_squote_whitelist;
	return (args);
}

t_error	context_dollar_squote(
	t_expander *state,
	t_expander_word *word,
	t_expander_word *word_exp)
{
	return (context_scan(state, context_dollar_squote_rules(word, word_exp)));
}
