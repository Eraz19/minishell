#include "context.h"
#include "quote_removal_context_.h"

t_error	context_heredoc(
	t_expander *state,
	t_expander_word_item item,
	t_expander_word *word,
	t_expander_word *word_exp)
{
	t_expander_word_item	escaped;

	if (item.c != '\\' || word->len == 0)
		return (state->err = expander_word_push(word_exp, item));
	state->err = expander_word_pop(word, &escaped);
	if (state->err.type)
		return (state->err);
	if (!is_in_context_heredoc_whitelist(escaped.c))
	{
		state->err = expander_word_push(word_exp, item);
		if (state->err.type)
			return (state->err);
	}
	return (state->err = expander_word_push(word_exp, escaped));
}
