#ifndef LOADER_CONTEXT__H
# define LOADER_CONTEXT__H

# include "context.h"
# include "loader_.h"

// ============= MAIN FUNCTIONS ================

bool	is_quoting_start(t_loader *loader);
bool	is_substitution_start(t_loader *loader);
t_error	loader_pop_context(t_loader *loader);
t_error	loader_push_context(t_loader *loader);

// ============= UTILS FUNCTIONS ================

bool	is_quoting_type(t_context context);
bool	is_context_start(t_loader *loader, t_context_stack_item **item);

#endif
