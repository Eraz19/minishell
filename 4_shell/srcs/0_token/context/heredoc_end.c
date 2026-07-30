#include "context.h"

bool	is_context_heredoc_ending(char c, void *_)
{
	return ((void)_, c == '\0');
}
