#include <stdlib.h>
#include "context.h"

bool	is_context_dquote_ending(char c, void *_)
{
	(void)_;
	return (c == '\"');
}

bool	is_context_squote_ending(char c, void *_)
{
	(void)_;
	return (c == '\'');
}

bool	is_quoting_ending(char c, t_context context)
{
	if (context == CONTEXT_SQUOTE)
		return (is_context_squote_ending(c, NULL));
	else if (context == CONTEXT_DQUOTE)
		return (is_context_dquote_ending(c, NULL));
	else if (context == CONTEXT_DOLLAR_SQUOTE)
		return (is_context_dollar_squote_ending(c, NULL));
	else
		return (false);
}

bool	is_context_dollar_squote_ending(char c, void *_)
{
	(void)_;
	return (c == '\'');
}
