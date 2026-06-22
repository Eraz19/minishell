#include "context.h"

bool	is_context_dollar_squote_start(char *str)
{
	return (str[1] != '\0' && str[0] == '$' && str[1] == '\'');
}

bool	is_in_context_dollar_squote_whitelist(char c)
{
	return ((void)c, true);
}

bool	is_context_dollar_squote_ending(char c, void *_)
{
	return (c == '\'');
}
