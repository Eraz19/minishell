#ifndef EXPANDER_WORD__H
# define EXPANDER_WORD__H

# include "error.h"
# include "libft.h"
# include "context.h"

typedef t_vector	t_expander_word;

typedef struct s_expander_word_item_opt
{
	size_t		i;
	t_context	quoted;
	t_context	context;
	bool		escaped;
	bool		is_expand_res;
}	t_expander_word_item_opt;

typedef struct s_expander_word_item
{
	char						c;
	t_expander_word_item_opt	opt;
}	t_expander_word_item;

void					expander_word_init(t_expander_word *word);
void					expander_word_free(t_expander_word *word);
t_expander_word_item	expander_word_item_init(
							char c,
							t_expander_word_item_opt opt);

t_error					expander_word_peek(
							t_expander_word *word,
							t_expander_word_item *item, size_t i);
t_error					expander_word_push(
							t_expander_word *word,
							t_expander_word_item item);
t_error					expander_word_pop(
							t_expander_word *word,
							t_expander_word_item *item);
t_error					expander_word_dup(
							t_expander_word *dst,
							t_expander_word *src);
t_error					expander_word_get(
							t_expander_word *word,
							size_t index, t_expander_word_item *item);
t_error					expander_word_remove(
							t_expander_word *word,
							size_t start, size_t len);
t_error					expander_word_to_str(
							t_expander_word *word,
							char **str,
							size_t start,
							size_t len);
t_error					expander_word_from_str(
							t_expander_word *word,
							const char *str,
							t_expander_word_item_opt opt);

#endif
	