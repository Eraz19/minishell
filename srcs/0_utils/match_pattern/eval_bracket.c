#include "match_pattern_.h"

bool	eval_range(const char *pattern, char c, size_t *i)
{
	char	end;
	char	start;

	start = pattern[*i];
	end = pattern[*i + 2];
	if (start <= c && c <= end)
		return ((*i) += 3, true);
	else
		return ((*i) += 3, false);
}

bool	eval_bracket_char(const char *pattern, char c, size_t *i)
{
	if (match_char(pattern[*i], c, i))
		return (true);
	else
		return ((*i)++, false);
}
