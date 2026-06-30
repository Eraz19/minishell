#ifndef EXPANDER_LOADER__H
# define EXPANDER_LOADER__H

# include "error.h"
# include "context.h"
# include "expander.h"
# include "expander_word_.h"
# include "expander_field_.h"

typedef struct s_expander_loader
{
	size_t					i;
	t_error					err;
	t_string				word;
	t_context_stack			stack;
	t_context				quoting;
	t_expander_word			loaded_word;
	t_context_stack			loading_stack;
	t_context_stack_item	*context_item;
}	t_expander_loader;

void	expander_loader_init(t_expander_loader *state);
void	expander_loader_free(t_expander_loader *state);
t_error	expander_loader_load(
			t_expander_loader *state,
			const t_context_stack *stack,
			t_string *word);

bool	is_char_escaped(t_expander_loader *state);
bool	is_quoting_start(t_expander_loader *state);
bool	is_substitution_start(t_expander_loader *state);
t_error	expander_loader_pop_context(t_expander_loader *state);
t_error	expander_loader_push_context(t_expander_loader *state);
t_error	expander_loader_consume(
			t_expander_loader *state,
			size_t count,
			bool escaped);

t_error	expander_loader_quoted(t_expander_loader *state);
t_error	expander_loader_substitution(t_expander_loader *state);

t_error	expander_loader_build(t_expander_loader *state);
t_error	expander_loader_extract(t_expander_fields *fields, t_expansion *out);
	
#endif
