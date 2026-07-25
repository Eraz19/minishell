#include "cmd.h"
#include "backtick_substitution_.h"

bool	is_backtick_substitution(t_word_item *current_item, uint flags)
{
	if (!flag_is_active((uint)flags, EXP_CMD_SUB))
		return (false);
	if (current_item->opt.context == CONTEXT_BACKTICK)
		return (true);
	return (false);
}

static t_error	merge_cmd_res_into_word_exp(
			t_expander *expander,
			t_word_item_opt *item_opt,
			t_string *cmd_res)
{
	t_word	word;

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
	expander->err = word_remove(&expander->word, 0, item_opt->context_len);
	return (word_free(&word), expander->err);
}

t_error	backtick_substitution(t_expander *expander)
{
	t_word_item	item;
	t_string	cmd_res;
	t_string	cmd_str;

	expander->err = word_get(&item, &expander->word, 0);
	if (expander->err.type)
		return (expander->err);
	expander->err = to_str(&cmd_str, &expander->word, 1,
						item.opt.context_len - 2);
	if (expander->err.type)
		return (expander->err);
	expander->err = cmd_sub_run_string(
						&cmd_str,
						&cmd_res,
						expander->exit_status);
	if (expander->err.type)
		return (string_free(&cmd_str), expander->err);
	string_free(&cmd_str);
	merge_cmd_res_into_word_exp(expander, &item.opt, &cmd_res);
	return (string_free(&cmd_res), expander->err);
}
