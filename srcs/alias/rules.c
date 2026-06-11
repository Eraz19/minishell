/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 13:54:53 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 19:11:48 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "context.h"
#include "builder.h"
#include "alias_stack_.h"

static bool	is_word_containing_quoting(char *word)
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

static bool	is_valid_alias_name(char *word)
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

bool	is_token_aligeable_to_alias_expansion(t_alias *state, char *word)
{
	if (is_word_containing_quoting(word))
		return (false);
	else if (!is_valid_alias_name(word))
		return (false);
	else if (!hashmap_contains(&state->map, word))
		return (false);
	else if (alias_stack_contains(&state->stack, word))
		return (false);
	else if (!state->disable_position && !builder_can_next_word_be_a_cmd_name())
		return (false);
	else
		return (true);
}
