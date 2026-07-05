#include "loader_.h"

bool	is_char_escaped(t_loader *loader)
{
	t_context	quoting;
	char		next_char;
	char		current_char;
	bool		is_in_whitelist;

	quoting = loader->quoting;
	current_char = loader->word.data[loader->i];
	next_char = loader->word.data[loader->i + 1];
	if (quoting != CONTEXT_NONE)
		is_in_whitelist = is_in_quoting_whitelist(next_char, quoting);
	else
		is_in_whitelist = is_in_substitution_whitelist(next_char, quoting);
	return (current_char == '\\' && next_char != '\0' && is_in_whitelist);
}

t_error	loader_consume(t_loader *loader, bool escaped)
{
	t_word_item_opt	opt;
	t_word_item		item;
	size_t			context_len;
	char			current_char;
	
	opt.escaped = escaped;
	opt.quoted = loader->quoting;
	opt.local_quoted = loader->local_quoting;
	opt.is_expand_res = false;
	if (loader->context_item == NULL)
	{
		opt.context = CONTEXT_NONE;
		opt.context_len = 0;
	}
	else
	{
		opt.context = loader->context_item->context;
		context_len = loader->context_item->end - loader->context_item->start;
		opt.context_len = context_len;
	}
	opt.i = loader->i;
	current_char = loader->word.data[loader->i++];
	item = word_item_init(current_char, opt);
	loader->err = word_push(&loader->loaded_word, item);
	return (loader->err);
}
