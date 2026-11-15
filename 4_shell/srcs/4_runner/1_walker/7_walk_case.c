/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_walk_case.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:23:41 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 21:02:38 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "walker_priv.h"
#include "expander.h"

#define CITATION	"POSIX 2.9.4.3: case shall execute \
the compound-list corresponding to the first pattern [...]\
 that is matched by the string resulting from [expansions]"

static inline t_error	walk_case_expand(
							t_token *token,
							t_string *dst,
							int *exit_status)
{
	t_error		err;
	t_exp_flag	flags;
	t_string	*expanded;
	t_expansion	expansion;

	flags = expansion_flags_case();
	err = expand_token(&expansion, token, exit_status, flags);
	if (err.type)
		return (err);
	if (expansion.len != 1)
		return (expansion_merge(token->value.data, CITATION, &expansion, dst));
	expanded = &((t_string *)expansion.data)[0];
	string_take_string(dst, expanded);
	expansion_free(&expansion);
	return (err);
}

static inline t_error	walk_case_token_matchs_word(
							t_string *word,
							t_token *token,
							bool *out,
							int *exit_status)
{
	t_exp_flag	flags;
	t_fields	pattern_list;
	size_t		i;
	t_word		*pattern;
	t_error		err;

	flags = expansion_flags_case();
	err = expand_token_word(&pattern_list, token, exit_status, flags);
	if (err.type)
		return (err);
	i = 0;
	while (i < pattern_list.len)
	{
		pattern = &((t_word *)pattern_list.data)[i];
		err = word_match_pattern(out, pattern, word->data, word->len);
		if (err.type || *out == true)
			break ;
		i++;
	}
	fields_free(&pattern_list);
	return (err);
}

static inline t_error	walk_case_match_pool(
							t_string *word,
							t_token_pool *pool,
							bool *out,
							int *exit_status)
{
	size_t	i;
	t_token	*token;
	t_error	err;

	i = 0;
	*out = false;
	err = error(ERR_NO);
	while (i < pool->len)
	{
		token = token_pool_get(pool, i);
		err = walk_case_token_matchs_word(word, token, out, exit_status);
		if (err.type || *out == true)
			return (err);
		i++;
	}
	return (err);
}

static inline t_error	walk_case_exec(
							t_runner *runner,
							t_ast_case *case_clause,
							size_t index,
							int *exit_status)
{
	t_ast_list	*list;
	bool		fallthrough;
	t_error		err;

	err = error(ERR_NO);
	while (index < case_clause->bodies.len)
	{
		list = &((t_ast_list *)case_clause->bodies.data)[index];
		fallthrough = ((bool *)case_clause->fallthrough.data)[index];
		err = walk_list(runner, list, exit_status);
		if (err.type || fallthrough == false)
			return (err);
		index++;
	}
	return (err);
}

t_error	walk_case(t_runner *runner, t_ast_case *case_clause, int *exit_status)
{
	t_string		word;
	size_t			i;
	t_token_pool	*pool;
	bool			match;
	t_error			err;

	err = walk_case_expand(&case_clause->word, &word, exit_status);
	if (err.type)
		return (err);
	match = false;
	i = 0;
	while (err.type == ERR_NO && i < case_clause->patterns.len)
	{
		pool = &((t_token_pool *)case_clause->patterns.data)[i];
		err = walk_case_match_pool(&word, pool, &match, exit_status);
		if (err.type == ERR_NO && match == true)
		{
			err = walk_case_exec(runner, case_clause, i, exit_status);
			break ;
		}
		i++;
	}
	if (err.type == ERR_NO && match == false)
		*exit_status = 0;
	return (string_free(&word), err);
}
