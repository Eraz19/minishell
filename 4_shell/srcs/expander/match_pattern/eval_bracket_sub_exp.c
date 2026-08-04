/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_bracket_sub_exp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:44:41 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:44:42 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "match_pattern_.h"

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
	if (pattern[*i + 2] == '\0' || pattern[*i + 3] != '.'
		|| pattern[*i + 4] != ']')
		return (eval_bracket_char(pattern, c, i));
	if (pattern[*i + 2] == c)
		return ((*i) += 5, true);
	else
		return ((*i) += 5, false);
}

bool	eval_equ_class_exp(const char *pattern, char c, size_t *i)
{
	if (pattern[*i + 2] == '\0' || pattern[*i + 3] != '='
		|| pattern[*i + 4] != ']')
		return (eval_bracket_char(pattern, c, i));
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
