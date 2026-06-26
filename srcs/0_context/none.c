#include "context.h"

bool	is_in_context_none_whitelist(char c)
{
	return ((void)c, true);
}

bool	is_context_none_ending(char c, void *_)
{
	return (c == '\0');
}

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}
