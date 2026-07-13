#ifndef PARAM_EXPANSION__H
# define PARAM_EXPANSION__H

# include "expander_.h"

t_error		param_expansion(t_expander *expander);

t_word_item	simple_dquote_item(t_word_item_opt opt);
t_error		drop_quoted_null_at(t_expander *expander);
bool		is_param_expansion(t_expander *expander, t_word_item *current_item);
t_error		emit_positionals(t_expander *expander, char c, t_word_item_opt opt);
t_error		get_param_name(
				t_expander *expander,
				t_string *param_name,
				bool braced);

#endif
