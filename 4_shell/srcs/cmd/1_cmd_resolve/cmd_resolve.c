/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_resolve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:56:12 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:58:21 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "cmd_resolve_priv.h"
#include "token.h"
#include "expander.h"

static inline void	cmd_resolve_name(t_cmd *cmd, bool *is_declaration_utility)
{
	*is_declaration_utility = cmd_resolve_is_declaration_utility(
			cmd->name.data);
	if (string_get_index_c(&cmd->name, '/') >= 0)
		cmd->entry.type = CMD_EXTERNAL;
	else if (cmd_resolve_is_special_builtin(cmd))
		return ;
	cmd_resolve_warn_if_unspecified(cmd->name.data);
	if (cmd_resolve_is_function(cmd))
		return ;
	else if (cmd_resolve_is_intrinsic_builtin(cmd))
		return ;
	cmd->entry.type = CMD_EXTERNAL;
}

// @ret ERR_LIBC
static inline t_error	cmd_add_to_argv(
							const t_expansion *expansion,
							t_cmd *cmd,
							bool *is_declaration_utility)
{
	t_string	*expanded_word;
	size_t		i;

	i = 0;
	while (i < expansion->len)
	{
		expanded_word = &((t_string *)expansion->data)[i];
		if (!vector_push(&cmd->argv, &expanded_word->data))
			return (error_sys());
		cmd->argc++;
		expanded_word->cap = 0;
		i++;
	}
	if (expansion->len > 0 && cmd->entry.type == CMD_NONE)
	{
		expanded_word = &((t_string *)expansion->data)[0];
		cmd->name.data = expanded_word->data;
		cmd->name.len = expanded_word->len;
		cmd_resolve_name(cmd, is_declaration_utility);
	}
	return (error(ERR_NO));
}

// @ret TODO
static inline t_error	cmd_expand_word(
							t_token *word,
							t_cmd *cmd,
							bool *is_declaration_utility,
							int *exit_status)
{
	t_exp_flag		flags;
	t_expansion		expansion;
	t_error			err;

	if (*is_declaration_utility == true && word->assignment_offset >= 0)
		flags = expansion_flags_assignment();
	else
		flags = expansion_flags_regular();
	err = expand_token(&expansion, word, exit_status, flags);
	if (err.type)
		return (err);
	err = cmd_add_to_argv(&expansion, cmd, is_declaration_utility);
	expansion_free(&expansion);
	return (err);
}

t_error	cmd_resolve(t_cmd *cmd, const t_token_pool *words, int *exit_status)
{
	size_t	index;
	char	*null;
	t_token	*word;
	bool	is_declaration_utility;
	t_error	err;

	is_declaration_utility = false;
	err = error(ERR_NO);
	index = 0;
	while (index < words->len && err.type == ERR_NO)
	{
		word = token_pool_get(words, index);
		err = cmd_expand_word(word, cmd, &is_declaration_utility, exit_status);
		index++;
	}
	if (err.type == ERR_NO)
	{
		null = NULL;
		if (!vector_push(&cmd->argv, &null))
			return (error_sys());
	}
	return (err);
}
