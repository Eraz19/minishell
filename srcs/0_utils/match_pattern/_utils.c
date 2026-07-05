#include "match_pattern_.h"

bool	match_char(char c1, char c2, size_t *len)
{
	if (c1 == c2)
		return ((*len)++, true);
	return (false);
}
