/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   API.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 17:10:12 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/12 17:08:06 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell.h"
#include "alias_.h"
#include "builder.h"
#include "context.h"
#include "alias_stack_.h"

t_error	alias_on_expansion_end(void)
{
	t_alias	*state;

	state = shell_get_alias();
	if (state == NULL)
		return (ERR_SHELL_NOT_FOUND);
	if (state->stack.len == 0)
		return (state->err);
	return (alias_stack_pop(&state->stack), state->err);
}

t_error	alias_print(const char *name)
{
	t_key_value	*pair;
	t_alias		*state;
	t_key_value	**pairs;

	state = shell_get_alias();
	if (state == NULL)
		return (ERR_SHELL_NOT_FOUND);
	if (name == NULL)
		return (alias_print_all(hashmap_get_all(&state->map)), state->err);
	else
	{
		pair = hashmap_get(&state->map, name);
		if (pair == NULL)
			return (state->err);
		pairs = malloc(sizeof(t_key_value *) * 2);
		if (pairs == NULL)
			return (state->err = ERR_LIBC);
		pairs[0] = pair;
		pairs[1] = NULL;
		return (alias_print_all(pairs), state->err);
	}
}

t_error	alias_remove(const char *name)
{
	t_alias	*state;

	state = shell_get_alias();
	if (state == NULL)
		return (ERR_SHELL_NOT_FOUND);
	if (name == NULL)
		return (state->err);
	return (hashmap_remove(&state->map, name), state->err);
}

t_error	alias_add(const char *name, const char *value)
{
	t_alias	*state;
	char	*value_copy;

	state = shell_get_alias();
	if (state == NULL)
		return (ERR_SHELL_NOT_FOUND);
	if (name == NULL)
		return (state->err);
	if (value == NULL)
		value_copy = str_dup("");
	else
		value_copy = str_dup(value);
	if (value_copy == NULL)
		return (state->err = ERR_LIBC);
	if (!hashmap_put(&state->map, name, (void *)value_copy))
		return (state->err = ERR_LIBC);
	return (state->err);
}

t_error	alias_expand_token(char **expansion, t_buff *token_value)
{
	t_alias	*state;
	char	*token_str;

	state = shell_get_alias();
	if (state == NULL)
		return (ERR_SHELL_NOT_FOUND);
	token_str = buff_get_string(token_value);
	if (token_str == NULL)
		return (state->err = ERR_LIBC);
	if (is_token_alias_expandable(state, token_str))
	{
		state->err = alias_stack_push(&state->stack, token_str);
		if (state->err)
			return (free(token_str), state->err);
		*expansion = hashmap_get(&state->map, token_str)->value;
		if (*expansion == NULL)
			return (state->err = ERR_INCOHERENT_STATE);
		*expansion = str_dup(*expansion);
		if (*expansion == NULL)
			return (state->err = ERR_LIBC);
		return (set_position_for_next_word(state, *expansion), state->err);
	}	
	return (free(token_str), state->err);
}
