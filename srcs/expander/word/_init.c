#include "expander_word_.h"

void		expander_word_init(t_expander_word *word)
{
	vector_init(word, sizeof(t_expander_word_item), 0);
}

void		expander_word_free(t_expander_word *word)
{
	vector_free(word, NULL);
}

t_expander_word_item	expander_word_item_init(
	char c,
	t_context quoted,
	t_context context,
	bool is_expand_res)
{
	t_expander_word_item	item;

	item.c = c;
	if (quoted != SQUOTE && quoted != DQUOTE && quoted != DOLLAR_SQUOTE)
		quoted = NONE_;
	item.opt.quoted = quoted;
	item.opt.context = context;
	item.opt.is_expand_res = is_expand_res;
	return (item);
}
