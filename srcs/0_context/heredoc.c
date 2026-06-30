#include "context.h"

bool	is_in_context_heredoc_whitelist(char c)
{
	return (c == '$' || c == '`' || c == '\\');
}

bool	is_context_heredoc_ending(char c, void *_)
{
	return ((void)_, c == '\0');
}
