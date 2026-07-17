#include "ast.h"
#include "cmd_sub.h"
#include "cmd_substitution_.h"

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

	expander->err = from_str(&word, cmd_res, *item_opt);
	if (expander->err.type)
		return (expander->err);
	while (word.len > 0)
	{
		expander->err = forward_word_item(&expander->word_exp, &word);
		if (expander->err.type)
			return (word_free(&word), expander->err);
	}
	expander->err = word_remove(&expander->word, 0, item_opt->context_len);
	return (word_free(&word), expander->err);
}

t_error	cmd_substitution(t_expander *expander)
{
	t_word_item	item;
	t_string	cmd_res;
	t_ast_root	*ast_root;

	expander->err = word_get(&item, &expander->word, 0);
	if (expander->err.type)
		return (expander->err);
	ast_vector_get()
	if (expander->err.type)
		return (string_free(&cmd_str), expander->err);
	string_free(&cmd_str);
	merge_cmd_res_into_word_exp(expander, &item.opt, &cmd_res);
	return (string_free(&cmd_res), expander->err);


	expander->err = error_print(error(ERR_NOT_IMPLEMENTED),
			__func__, NULL, NULL);
	return (expander->err);
}
