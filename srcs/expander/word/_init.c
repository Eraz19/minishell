#include "expander_word_.h"

void	expander_word_init(t_expander_word *word)
{
	vector_init(word, sizeof(t_expander_word_item), 0);
}

void	expander_word_free(t_expander_word *word)
{
	vector_free(word, NULL);
}

t_expander_word_item	expander_word_item_init(
							char c,
							t_expander_word_item_opt opt)
{
	t_expander_word_item	item;

	item.c = c;
	if (opt.quoted != CONTEXT_SQUOTE 
		&& opt.quoted != CONTEXT_DQUOTE
		&& opt.quoted != CONTEXT_DOLLAR_SQUOTE)
		opt.quoted = CONTEXT_NONE;
	item.opt = opt;
	return (item);
}
