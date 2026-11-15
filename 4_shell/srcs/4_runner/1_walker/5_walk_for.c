/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_walk_for.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:23:36 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:29:05 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "walker_priv.h"
#include "expander.h"
#include "env.h"

static inline t_error	walk_for_expand_default_word(
							t_expansions *expansions,
							t_exp_flag flags,
							int *exit_status)
{
	t_string	synthetic_word;
	t_expansion	expansion;
	t_error		err;

	if (!string_init(&synthetic_word, 0, "\"$@\"", -1))
		return (error_sys());
	err = expand_str(&expansion, &synthetic_word, exit_status, flags);
	string_free(&synthetic_word);
	if (err.type)
		return (err);
	if (!vector_push(expansions, &expansion))
		return (err = error_sys(), expansion_free(&expansion), err);
	return (err);
}

static inline t_error	walk_for_expand_words(
							t_token_pool *pool,
							bool has_in,
							t_expansions *expansions,
							int *exit_status)
{
	size_t		i;
	t_token		*token;
	t_exp_flag	flags;
	t_expansion	expansion;
	t_error		err;

	flags = expansion_flags_regular();
	if (pool->len == 0 && has_in == false)
		return (walk_for_expand_default_word(expansions, flags, exit_status));
	i = 0;
	while (i < pool->len)
	{
		token = token_pool_get(pool, i++);
		err = expand_token(&expansion, token, exit_status, flags);
		if (err.type)
			return (err);
		if (expansion.len == 0)
		{
			expansion_free(&expansion);
			continue ;
		}
		if (!vector_push(expansions, &expansion))
			return (err = error_sys(), expansion_free(&expansion), err);
	}
	return (error(ERR_NO));
}

static inline t_error	walk_for_word_list(
							t_runner *runner,
							t_ast_for *for_clause,
							t_expansion *expansion,
							int *exit_status)
{
	size_t		i;
	t_string	*word;
	t_error		err;

	i = 0;
	err = error(ERR_NO);
	while (i < expansion->len)
	{
		word = &((t_string *)expansion->data)[i++];
		err = env_set_variable(
				&for_clause->var_name.value, word, false, false);
		if (err.type == ERR_NO)
			err = walk_list(runner, &for_clause->body, exit_status);
		if (walk_loop_must_continue(runner, &err) == true)
			continue ;
		if (err.type)
			return (err);
	}
	return (err);
}

static inline t_error	walk_for_loop(
							t_runner *runner,
							t_ast_for *for_clause,
							t_expansions *expansions,
							int *exit_status)
{
	size_t		i;
	t_expansion	*expansion;
	t_error		err;

	if (expansions->len == 0)
		return (*exit_status = 0, error(ERR_NO));
	i = 0;
	while (i < expansions->len)
	{
		expansion = &((t_expansion *)expansions->data)[i];
		err = walk_for_word_list(runner, for_clause, expansion, exit_status);
		if (walk_loop_must_break(runner, &err) == true)
			break ;
		if (err.type)
			return (err);
		i++;
	}
	return (err);
}

t_error	walk_for(t_runner *runner, t_ast_for *for_clause, int *exit_status)
{
	t_expansions	expansions;
	t_error			err;

	runner->loop_depth++;
	cmd_expansions_init(&expansions);
	err = walk_for_expand_words(
			&for_clause->words,
			for_clause->has_in,
			&expansions,
			exit_status);
	if (err.type == ERR_NO)
		err = walk_for_loop(runner, for_clause, &expansions, exit_status);
	cmd_expansions_free(&expansions);
	runner->loop_depth--;
	return (err);
}
