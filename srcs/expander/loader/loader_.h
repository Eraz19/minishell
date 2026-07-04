#ifndef LOADER__H
# define LOADER__H

# include "word_.h"
# include "error.h"
# include "context.h"
# include "expander_.h"

typedef struct s_loader
{
	size_t					i;
	t_error					err;
	t_string				word;
	t_context_stack			stack;
	t_context				quoting;
	t_word					loaded_word;
	t_context_stack			loading_stack;
	t_context_stack_item	*context_item;
}	t_loader;

void	loader_init(t_loader *loader);
void	loader_free(t_loader *loader);
t_error	loader_load(t_loader *loader, t_expander_args *args);

// ============= MAIN FUNCTIONS ================

t_error	loader_quoted(t_loader *loader);
t_error	loader_prepare_word(t_loader *loader);

// ============= UTILS FUNCTIONS ================

bool	is_char_escaped(t_loader *loader);
t_error	loader_consume(t_loader *loader, bool escaped);
	
#endif
