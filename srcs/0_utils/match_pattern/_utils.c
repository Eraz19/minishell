#include "libft.h"
#include "match_pattern_.h"

bool	match_char(char c1, char c2, size_t *len)
{
	if (c1 == c2)
		return ((*len)++, true);
	return (false);
}

bool	ft_isxdigit(char c)
{
	return (ft_isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}


bool	set_negation(const char *pattern, size_t *i)
{
	if (*pattern == '!' || *pattern == '^')
		return ((*i)++, true);
	else
		return (false);
}
