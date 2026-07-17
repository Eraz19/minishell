#include "cmd_sub.h"
#include "cmd_substitution_.h"
# include <stdio.h>	// DEBUG

bool	is_cmd_substitution(t_word_item *current_item, uint flags)
{
	if (!flag_is_active((uint)flags, EXP_CMD_SUB))
		return (false);
	if (current_item->opt.context == CONTEXT_CMD_SUB)
		return (true);
	return (false);
}

static t_error	merge_cmd_res_into_word_exp(
			t_expander *expander,
			t_word_item_opt *item_opt,
			t_string *cmd_res)
{
	t_word	word;

	fprintf(stderr, "%s() cmd_res.len = %zu\n", __func__, cmd_res->len);
	item_opt->is_expand_res = true;
	expander->err = from_str(&word, cmd_res, *item_opt);
	if (expander->err.type)
		return (expander->err);
	while (word.len > 0)
	{
		expander->err = forward_word_item(&expander->word_exp, &word);
		if (expander->err.type)
			return (word_free(&word), expander->err);
	}
	fprintf(stderr, "%s() %zu\n", __func__, item_opt->context_len);
	expander->err = word_remove(&expander->word, 0, item_opt->context_len + 1);
	return (word_free(&word), expander->err);
}

t_error	cmd_substitution(t_expander *expander)
{
	t_word_item	item;
	t_string	cmd_res;

	expander->err = word_get(&item, &expander->word, 0);
	if (expander->err.type)
		return (expander->err);
	fprintf(stderr, "%s() %c\n", __func__, item.c);
	expander->err = cmd_sub_run_ast(
						expander->ast_vec,
						expander->ast_i,
						&cmd_res,
						expander->exit_status);
	if (expander->err.type)
		return (expander->err);
	++expander->ast_i;
	merge_cmd_res_into_word_exp(expander, &item.opt, &cmd_res);
	return (string_free(&cmd_res), expander->err);
}
