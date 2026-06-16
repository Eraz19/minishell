/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 10:40:13 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/12 17:04:17 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "alias_.h"
#include "builder.h"
#include "context.h"
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

void	alias_print_all(t_key_value **pairs)
{
	size_t	i;

	if (pairs == NULL)
		return ;
	i = 0;
	while (pairs[i] != NULL)
	{
		if (pairs[i]->value == NULL)
			ft_printf("%s=''\n", pairs[i]->key);
		else
			ft_printf("%s='%s'\n", pairs[i]->key, (char *)pairs[i]->value);
		i++;	
	}
	free(pairs);
}

bool	is_token_alias_expandable(t_alias *state, char *word)
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

void	set_position_for_next_word(t_alias *state, char *expansion)
{
	size_t	expansion_len;
	
	if (expansion == NULL)
		return ;
	expansion_len = str_len(expansion);
	if (expansion != NULL && is_blank(expansion[expansion_len - 1]))
		state->disable_position = true;
	else
		state->disable_position = false;
}
