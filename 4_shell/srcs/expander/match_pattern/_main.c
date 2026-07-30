#include "libft.h"
#include "expander_.h"
#include "match_pattern_.h"

bool	match_bracket_c(const char *pattern, size_t len, char c)
{
	size_t	i;
	bool	is_negated;

	i = 1;
	is_negated = set_negation(pattern + 1, &i);
	while (i <= len)
	{
		if (pattern[i] == '\\')
		{
			if (eval_escaped_char(pattern, c, &i))
				return (!is_negated);
		}
		else if (pattern[i + 1] == '-' && pattern[i + 2] != ']'
			&& pattern[i + 2] != '\\')
		{
			if (eval_range(pattern, c, &i))
				return (!is_negated);
		}
		else if (pattern[i] == '[')
		{
			if (eval_sub_exp(pattern, c, &i))
				return (!is_negated);
		}
		else if (eval_bracket_char(pattern, c, &i))
			return (!is_negated);
	}
	return (is_negated);
}

bool	valid_bracket_exp_len(const char *pattern, size_t *len)
{
	if (pattern[*len] == '!' || pattern[*len] == '^')
		(*len)++;
	if (pattern[*len] == ']')
		(*len)++;
	while (pattern[*len] != '\0' && pattern[*len] != ']')
	{
		if (pattern[*len] == '\\' && pattern[(*len) + 1] != '\0')
			(*len) += 2;
		else if (match_char(pattern[*len], '[', len))
			valid_sub_exp_len(pattern, len);
		else
			(*len)++;
	}
	if (pattern[*len] == ']')
		return (true);
	return (false);
}

bool	match_bracket(const char *pattern, const char *str, size_t len)
{
	size_t	exp_len;

	if (len == 0)
		return (false);
	exp_len = 0;
	if (valid_bracket_exp_len(pattern + 1, &exp_len))
	{
		if (match_bracket_c(pattern, exp_len, *str))
			return (match_pattern(pattern + exp_len + 2, str + 1, len - 1));
	}
	else if (*str == '[')
		return (match_pattern(pattern + 1, str + 1, len - 1));
	return (false);
}

bool	match_asterisk(const char *pattern, const char *str, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	pattern_len;

	i = 0;
	pattern_len = str_len(pattern);
	while (i < pattern_len && pattern[i] == '*')
		i++;
	if (i == pattern_len)
		return (true);
	j = 0;
	while (j < len)
	{
		if (match_pattern(pattern + i, str + j, len - j))
			return (true);
		j++;
	}
	return (false);
}

bool	match_pattern(const char *pattern, const char *str, size_t len)
{
	if (*pattern == '\0')
		return (len == 0);
	else if (*pattern == '\\')
	{
		if (pattern[1] == '\0')
			return (len == 0);
		else if (len > 0 && pattern[1] == *str)
			return (match_pattern(pattern + 2, str + 1, len - 1));
	}
	else if (*pattern == '*')
		return (match_asterisk(pattern, str, len));
	else if (*pattern == '?')
	{
		if (len == 0)
			return (false);
		return (match_pattern(pattern + 1, str + 1, len - 1));
	}
	else if (*pattern == '[')
		return (match_bracket(pattern, str, len));
	else if (len > 0 && *pattern == *str)
		return (match_pattern(pattern + 1, str + 1, len - 1));
	return (false);
}
