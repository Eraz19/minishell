#ifndef QUOTE_REMOVAL_CONTEXT__H
# define QUOTE_REMOVAL_CONTEXT__H

#include "expander_.h"

typedef struct s_context_args
{
	t_expander_word	*word;
	t_context		context;
	t_expander_word	*word_expanded;
	bool			(*is_end)(char, void *);
	bool			(*is_in_whitelist)(char);
}	t_context_args;

t_error	context_scan(t_expander *state, t_context_args args);

t_error	context_squote(t_expander *state, t_expander_word *word,
			t_expander_word *word_exp);
t_error	context_dquote(t_expander *state, t_expander_word *word,
			t_expander_word *word_exp);
t_error	context_heredoc(t_expander *state, t_expander_word_item item,
			t_expander_word *word, t_expander_word *word_exp);
t_error	context_dollar_squote(t_expander *state, t_expander_word *word,
			t_expander_word *word_exp);

#endif
