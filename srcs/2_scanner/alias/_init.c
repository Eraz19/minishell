/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:29:09 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/08 14:49:55 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "__alias.h"
#include "__lexer_token.h"

void	alias_init(t_alias *state)
{
	*state = (t_alias){0};
	alias_stack_init(&state->stack);	
}

void	alias_free(t_alias *state)
{
	free(state->name);
	alias_stack_free(&state->stack);
	*state = (t_alias){0};
}

t_error	alias_load(t_alias *state, t_token *token)
{
	state->name = buff_get_string(&token->value);
	if (state->name == NULL)
		return (state->err = ERR_LIBC, state->err);
	return (state->err);
}
