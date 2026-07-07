#ifndef WORD__H
# define WORD__H

# include "error.h"
# include "libft.h"
# include "context.h"

// Forward type
typedef t_vector	t_fields;

typedef t_vector	t_word;

typedef struct s_word_item_opt
{
	size_t		i;
	t_context	quoted;
	t_context	local_quoted;
	t_context	context;
	bool		escaped;
	size_t		context_len;
	bool		is_expand_res;
}	t_word_item_opt;

typedef struct s_word_item
{
	char			c;
	t_word_item_opt	opt;
}	t_word_item;

void		word_init(t_word *word);
void		word_free(t_word *word);
t_word_item	word_item_init(char c, t_word_item_opt opt);

// ============= MAIN FUNCTIONS ================

t_error		word_dup(t_word *out, t_word *src);
t_error		word_fpop(t_word_item *out, t_word *word);
t_error		word_push(t_word *word, t_word_item item);
t_error		word_remove(t_word *word, size_t start, size_t len);
t_error		word_get(t_word_item *out, const t_word *word, size_t index);

// ============= CONVERTION FUNCTIONS ================

t_error		from_str(t_word *out, const t_string *src, t_word_item_opt opt);
t_error		to_str(t_string *out, const t_word *src, size_t start, size_t len);

#endif
	