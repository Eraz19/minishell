#ifndef QUOTE_REMOVAL_CONTEXT__H
# define QUOTE_REMOVAL_CONTEXT__H

#include "expander_.h"

typedef struct s_context_args
{
	t_word		*word;
	t_word		*word_expanded;
	bool		(*is_end)(char, void *);
	bool		(*is_in_whitelist)(char);
}	t_context_args;

t_error	context_scan(t_expander *expander, t_context_args args);

t_error	context_squote(t_expander *expander);
t_error	context_dquote(t_expander *expander);
t_error	context_dollar_squote(t_expander *expander);
t_error	context_heredoc(t_expander *expander, t_word_item item);

#endif
