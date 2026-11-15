/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_reserved_words.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 14:51:11 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:41:46 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grammar_qualifiers_priv.h"
#include "libft.h"
#include <stdlib.h>

static inline t_symbol	str_to_reserved_word_2(const char *token_value)
{
	if (str_cmp(token_value, "elif") == 0)
		return (SYM_Elif);
	else if (str_cmp(token_value, "else") == 0)
		return (SYM_Else);
	else if (str_cmp(token_value, "fi") == 0)
		return (SYM_Fi);
	else if (str_cmp(token_value, "for") == 0)
		return (SYM_For);
	else if (str_cmp(token_value, "in") == 0)
		return (SYM_In);
	else if (str_cmp(token_value, "until") == 0)
		return (SYM_Until);
	else if (str_cmp(token_value, "while") == 0)
		return (SYM_While);
	return (SYM_error);
}

static inline t_symbol	str_to_reserved_word(const char *token_value)
{
	if (str_cmp(token_value, "!") == 0)
		return (SYM_Bang);
	else if (str_cmp(token_value, "{") == 0)
		return (SYM_Lbrace);
	else if (str_cmp(token_value, "}") == 0)
		return (SYM_Rbrace);
	else if (str_cmp(token_value, "case") == 0)
		return (SYM_Case);
	else if (str_cmp(token_value, "esac") == 0)
		return (SYM_Esac);
	else if (str_cmp(token_value, "do") == 0)
		return (SYM_Do);
	else if (str_cmp(token_value, "done") == 0)
		return (SYM_Done);
	else if (str_cmp(token_value, "if") == 0)
		return (SYM_If);
	else if (str_cmp(token_value, "then") == 0)
		return (SYM_Then);
	return (str_to_reserved_word_2(token_value));
}

bool	qualify_try_reserved_word(
			char *token_value,
			ssize_t assignment_offset,
			t_symbol *out_symbol)
{
	t_symbol	symbol;

	(void)assignment_offset;
	symbol = str_to_reserved_word(token_value);
	if (symbol == SYM_error)
		return (false);
	*out_symbol = symbol;
	return (true);
}
