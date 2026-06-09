/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 13:54:53 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/08 16:29:40 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "__alias.h"
#include "context.h"

bool	builder_can_next_token_be_a_simple_cmd_name(void);

bool	is_word_containing_quoting(char *word)
{
	size_t	i;

	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '\'' ||
			is_context_squote_start(word + i) ||
			is_context_dquote_start(word + i) ||
			is_context_dollar_squote_start(word + i))
			return (true);
		i++;
	}
	return (false);
}

bool	is_valid_alias_name(char *word)
{
	size_t	i;

	i = 0;
	while (word[i] != '\0')
	{
		if (!ft_isalnum(word[i]) &&
			word[i] != '_' &&
			word[i] != '!' &&
			word[i] != '%' &&
			word[i] != ',' &&
			word[i] != '@' &&
			word[i] != '.')
			return (false);
		i++;
	}
	return (true);
}

t_error	alias_substitution()
{
	
}
