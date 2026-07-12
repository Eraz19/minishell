#include "error.h"
#include "walker_priv.h"
#include "expander.h"
#include "cmd_expansion.h"
#include "params.h"

static inline t_error	walk_for_expand_words(
							t_token_pool *pool,
							t_cmd_expansions *expansions)
{
	size_t		i;
	t_token		*token;
	t_exp_flag	flags;
	t_expansion	expansion;
	t_error		err;

	i = 0;
	flags = cmd_regular_expansion_flags();
	err = error(ERR_NO);
	while (i < pool->len)
	{
		token = token_pool_get(pool, i++);
		err = expand_token(&expansion, token, flags);
		if (err.type)
			break ;
		if (expansion.len == 0)
		{
			expansion_free(&expansion);
			continue ;
		}
		if (!vector_push(expansions, &expansion))
			return (err = error_sys(), expansion_free(&expansion), err);
	}
	return (err);
}

static inline t_error	walk_for_word(
							t_runner *runner,
							t_ast_for *for_clause,
							t_string *word,
							int *exit_status)
{
	t_error	err;

	err = params_set_variable(&for_clause->var_name.value, word, false, false);
	if (err.type)
		return (err);
	return (walk_list(runner, &for_clause->body, exit_status));
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
		err = walk_for_word(runner, for_clause, word, exit_status);
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
							t_cmd_expansions *expansions,
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
	t_cmd_expansions	expansions;
	t_error				err;

	runner->loop_depth++;
	*exit_status = -1;
	cmd_expansions_init(&expansions);
	err = walk_for_expand_words(&for_clause->words, &expansions);
	if (err.type == ERR_NO)
		err = walk_for_loop(runner, for_clause, &expansions, exit_status);
	cmd_expansions_free(&expansions);
	runner->loop_depth--;
	return (walk_normalize_output(err, NULL, exit_status));
}
