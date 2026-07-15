#include "error.h"
#include "walker_priv.h"
#include "expander.h"
#include "cmd_expansion.h"
#include "utils.h"
#include <assert.h>

static inline t_error	walk_case_expand(
							t_token *token,
							t_string *dst,
							int *exit_status)
{
	t_exp_flag	flags;
	t_string	*expanded;
	t_expansion	expansion;
	t_error		err;

	flags = cmd_case_expansion_flags();
	err = expand_token(&expansion, token, exit_status, flags);
	if (err.type)
		return (err);
	assert(expansion.len == 1);
	expanded = &((t_string *)expansion.data)[0];
	string_take_string(dst, expanded);
	expansion_free(&expansion);
	return (err);
}

static inline t_error	walk_case_token_matchs_word(
							t_string *expanded_word,
							t_token *token,
							bool *out,
							int *exit_status)
{
	t_string	expanded_token;
	t_error		err;

	err = walk_case_expand(token, &expanded_token, exit_status);
	if (err.type)
		return (err);
	*out = match_pattern(
			expanded_token.data,
			expanded_word->data,
			expanded_word->len);
	string_free(&expanded_token);
	return (err);
}

static inline t_error	walk_case_match_pool(
							t_string *expanded_word,
							t_token_pool *pool,
							bool *out,
							int *exit_status)
{
	size_t	i;
	t_token *token;
	t_error	err;

	i = 0;
	*out = false;
	err = error(ERR_NO);
	while (i < pool->len)
	{
		token = token_pool_get(pool, i);
		err = walk_case_token_matchs_word(
				expanded_word,
				token,
				out,
				exit_status);
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

	assert(case_clause->bodies.len == case_clause->fallthrough.len);
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

	assert(case_clause->patterns.len == case_clause->bodies.len);
	assert(case_clause->bodies.len == case_clause->fallthrough.len);
	*exit_status = -1;
	err = walk_case_expand(&case_clause->word, &word, exit_status);
	if (err.type)
		return (walk_normalize_output(err, NULL, exit_status));
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
	if (err.type == ERR_NO && (i == 0 || match == false))
		*exit_status = 0;
	return (string_free(&word), walk_normalize_output(err, NULL, exit_status));
}
