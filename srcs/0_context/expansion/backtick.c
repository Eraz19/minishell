#include "context.h"

bool	is_context_backtick_start(char *str)
{
	return (str[0] == '`');
}

bool	is_in_context_backtick_special_whitelist(char c)
{
	return (c == '$' || c == '`' || c == '"' || c == '\\');
}

bool	is_in_context_backtick_whitelist(char c)
{
    return (c == '\\' || c == '$' || c == '`');
}

bool	is_context_backtick_ending(char c, void *_)
{
	return (c == '`');
}
