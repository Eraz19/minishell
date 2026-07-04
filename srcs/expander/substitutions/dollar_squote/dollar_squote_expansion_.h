#ifndef DOLLAR_SQUOTE_EXPANSION__H
# define DOLLAR_SQUOTE_EXPANSION__H

# include "expander_.h"

t_error			dollar_squote_expansion(t_expander *expander);
bool			is_dollar_squote_expansion(
					t_word_item *current_item,
					uint flags);

t_word_item_opt	dollar_squote_result_opt(t_word_item_opt in);
t_error			dollar_squote_emit(
					t_expander *expander,
					char c,
					t_word_item_opt opt);
t_error			dollar_squote_read_number(
					t_expander *expander,
					int base,
					size_t max,
					uint *value);
bool			dollar_squote_build_map(t_hashmap *escapes);

t_error			dollar_squote_escape(
					t_expander *expander,
					t_word_item_opt opt,
					t_hashmap *escapes);

t_error			dollar_squote_control_escape(
					t_expander *expander,
					t_word_item_opt opt);
t_error			dollar_squote_numeric_escape(
					t_expander *expander,
					t_word_item_opt opt);

#endif
