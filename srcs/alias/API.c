/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   API.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 17:10:12 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 19:17:34 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (ERR_NO);
	return (alias_stack_pop(&state->stack), ERR_NO);
}

t_error	alias_print(const char *name)
{
	t_alias	*state;

	state = shell_get_alias();
	if (state == NULL)
		return (ERR_SHELL_NOT_FOUND);
	if (name == NULL)
		alias_print_all(hashmap_get_all(&state->map));
	else
		alias_print_one(hashmap_get(&state->map, name));
	return (ERR_NO);
}

t_error	alias_remove(const char *name)
{
	t_alias	*state;

	state = shell_get_alias();
	if (state == NULL)
		return (ERR_SHELL_NOT_FOUND);
	if (name == NULL)
		return (ERR_NO);
	return (hashmap_remove(&state->map, name));
}

t_error	alias_add(const char *name, const char *value)
{
	t_alias	*state;
	char	*value_copy;

	state = shell_get_alias();
	if (state == NULL)
		return (ERR_SHELL_NOT_FOUND);
	if (name == NULL)
		return (ERR_NO);
	value_copy = str_dup(value);
	if (value != NULL && value_copy == NULL)
		return (ERR_LIBC);
	return (hashmap_put(&state->map, name, (void *)value_copy));
}

t_error	alias_expand_token(char **expansion, t_buff *token_value)
{
	t_error	err;
	t_alias	*state;
	char	*token_str;
	size_t	expansion_len;

	*expansion = NULL;
	state = shell_get_alias();
	if (state == NULL)
		return (ERR_SHELL_NOT_FOUND);
	token_str = buff_get_string(token_value);
	if (token_str == NULL)
		return (ERR_LIBC);
	if (is_token_aligeable_to_alias_expansion(state, token_str))
	{
		err = alias_stack_push(&state->stack, token_str);
		if (err != ERR_NO)
			return (err);
		*expansion = hashmap_get(&state->map, token_str)->value;
		expansion_len = str_len(*expansion);
		if (*expansion != NULL && is_blank((*expansion)[expansion_len - 1]))
			state->disable_position = true;
		else
			state->disable_position = false;
	}	
	return (ERR_NO);
}
