#include "context.h"

bool	is_in_context_heredoc_whitelist(char c)
{
	return (c == '$' || c == '`' || c == '\\');
}
