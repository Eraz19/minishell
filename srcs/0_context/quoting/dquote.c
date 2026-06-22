#include "context.h"

bool	is_context_dquote_start(char *str)
{
	return (str[0] == '\"');
}

bool	is_in_context_dquote_whitelist(char c)
{
	return (c == '$' || c == '`' || c == '\\' || c == '\"');
}

bool	is_context_dquote_ending(char c, void *_)
{
	return (c == '\"');
}
