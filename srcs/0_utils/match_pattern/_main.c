#include "libft.h"
#include "match_pattern_.h"

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


bool	eval_char_class_exp_content(const char *pattern, char c, size_t *i)
{
	if (str_ncmp(pattern + *i, "alpha", 5) == 0)
		return (*i += 5, ft_isalpha(c));
	else if (str_ncmp(pattern + *i, "digit", 5) == 0)
		return (*i += 5, ft_isdigit(c));
	else if (str_ncmp(pattern + *i, "alnum", 5) == 0)
		return (*i += 5, ft_isalnum(c));
	else if (str_ncmp(pattern + *i, "xdigit", 6) == 0)
		return (*i += 6, ft_isxdigit(c));
	else if (str_ncmp(pattern + *i, "lower", 5) == 0)
		return (*i += 5, c >= 'a' && c <= 'z');
	else if (str_ncmp(pattern + *i, "upper", 5) == 0)
		return (*i += 5, c >= 'A' && c <= 'Z');
	else if (str_ncmp(pattern + *i, "space", 5) == 0)
		return (*i += 5, ft_isspace(c));
	else if (str_ncmp(pattern + *i, "blank", 5) == 0)
		return (*i += 5, c == ' ' || c == '\t');
	else if (str_ncmp(pattern + *i, "cntrl", 5) == 0)
		return (*i += 5, (u_char)c < 0x20 || (u_char)c == 0x7F);
	else if (str_ncmp(pattern + *i, "graph", 5) == 0)
		return (*i += 5, ft_isprint(c) && c != ' ');
	else if (str_ncmp(pattern + *i, "print", 5) == 0)
		return (*i += 5, ft_isprint(c));
	else if (str_ncmp(pattern + *i, "punct", 5) == 0)
		return (*i += 5, ft_isprint(c) && !ft_isalnum(c) && c != ' ');
	return (false);
}

bool	eval_char_class_exp(const char *pattern, char c, size_t *i)
{
	size_t	i_copy;

	i_copy = *i;
	(*i) += 2;
	if (valid_char_class_exp_len(pattern, i))
	{
		*i = i_copy + 2;
		if (eval_char_class_exp_content(pattern, c, i))
			return (true);
		else
			return ((*i) += 2, false);
	}
	return (*i = i_copy, eval_bracket_char(pattern, c, i));
}

bool	eval_col_symbol_exp(const char *pattern, char c, size_t *i)
{
	if (pattern[*i + 2] == c)
		return ((*i) += 5, true);
	else
		return ((*i) += 5, false);
}

bool	eval_equ_class_exp(const char *pattern, char c, size_t *i)
{
	if (pattern[*i + 2] == c)
		return ((*i) += 5, true);
	else
		return ((*i) += 5, false);
}

bool	eval_sub_exp(const char *pattern, char c, size_t *i)
{
	if (pattern[(*i) + 1] == ':')
	{
		if (eval_char_class_exp(pattern, c, i))
			return (true);
	}
	else if (pattern[(*i) + 1] == '.')
	{
		if (eval_col_symbol_exp(pattern, c, i))
			return (true);
	}
	else if (pattern[(*i) + 1] == '=')
	{
		if (eval_equ_class_exp(pattern, c, i))
			return (true);
	}
	else
		return (eval_bracket_char(pattern, c, i));
	return (false);
}










bool	match_bracket_c(const char *pattern, size_t len, char c)
{
	size_t	i;
	bool	is_negated;

	i = 1;
	is_negated = set_negation(pattern + 1, &i);
	while (i <= len)
	{
		if (pattern[i + 1] == '-' && pattern[i + 2] != ']')
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
		if (match_char(pattern[*len], '[', len))
			valid_sub_exp_len(pattern, len);
		else
			(*len)++;
	}
	if (pattern[*len] == ']')
		return (true);
	return (false);
}

bool	match_bracket(const char *pattern, const char *str)
{
	size_t	len;

	if (*str == '\0')
		return (false);
	len = 0;
	if (valid_bracket_exp_len(pattern + 1, &len))
	{
		if (match_bracket_c(pattern, len, *str))
			return (match_pattern(pattern + len + 2, str + 1));
	}
	else if (*str == '[')
		return (match_pattern(pattern + 1, str + 1));
	return (false);
}

bool	match_asterisk(const char *pattern, const char *str)
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
	while (str[j] != '\0')
	{
		if (match_pattern(pattern + i, str + j))
			return (true);
		j++;
	}
	return (false);
}

bool	match_pattern(const char *pattern, const char *str)
{
	if (*pattern == '\0')
		return (*str == '\0');
	else if (*pattern == '\\')
	{
		if (pattern[1] == *str)
		{
			if (pattern[1] == '\0')
				return (*str == '\0');
			else
				return (match_pattern(pattern + 2, str + 1));
		}
	}
	else if (*pattern == '*')
		return (match_asterisk(pattern, str));
	else if (*pattern == '?')
	{
		if (*str == '\0')
			return (false);
		return (match_pattern(pattern + 1, str + 1));
	}
	else if (*pattern == '[')
		return (match_bracket(pattern, str));
	else if (*pattern == *str)
		return (match_pattern(pattern + 1, str + 1));
	return (false);
}
