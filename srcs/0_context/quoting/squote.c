#include "context.h"

bool	is_context_squote_start(char *str)
{
	return (str[0] == '\'');
}

bool	is_in_context_squote_whitelist(char c)
{
	return ((void)c, false);
}

bool	is_context_squote_ending(char c, void *_)
{
	return (c == '\'');
}
