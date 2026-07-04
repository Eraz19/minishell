#ifndef FIELD_SPLITTING__H
# define FIELD_SPLITTING__H

# include "expander_.h"

t_error	field_splitting(t_expander *state);

bool	is_it_white_space_ifs(char c);
t_error	delim_field(t_expander *expander);
bool	is_delim(t_word_item item, const t_string *ifs);
t_error	consume_word_item(t_expander *expander, t_word_item item);
t_error	fields_splitting_on_ifs_white_space(t_expander *expander);
t_error	fields_splitting_on_ifs_non_white_space(t_expander *expander);

#endif
