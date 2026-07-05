#include "param_braced_.h"
#include "param_unbraced_.h"

t_error	param_expansion(t_expander *expander)
{
	t_word_item	item;

	expander->err = word_get(&item, &expander->word, 1);
	if (expander->err.type)
		return (expander->err);
	if (item.c == '{')
		return (expand_braced(expander));
	else
		return (expand_unbraced(expander));
}
