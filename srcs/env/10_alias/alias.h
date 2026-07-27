#ifndef ALIAS_H
# define ALIAS_H

# include "alias_table_internal.h"
# include "alias_stack_internal.h"
# include "alias_forbidden_internal.h"

typedef struct s_alias
{
	t_alias_table		table;
	t_alias_stack		stack;
	t_alias_forbidden	forbidden;
}	t_alias;

// life cycle

void	alias_init(t_alias *alias);
void	alias_clear_stack(t_alias *alias);
void	alias_clear_forbidden(t_alias *alias);
void	alias_clear(t_alias *alias);
void	alias_free(t_alias *alias);

// ops

t_error	alias_set(t_alias *alias, const char *name, const t_string *value);
t_error	alias_get(
			t_alias *alias,
			const t_string *name,
			const t_string **out_value,
			bool add_to_stack);
bool	alias_is_forbidden(t_alias *alias, const char *name);
void	alias_pop_from_stack(t_alias *alias);
t_error	alias_unset(t_alias *alias, const char *name);
t_error	alias_print_one(t_alias *alias, const char *name);
t_error	alias_print_all(t_alias *alias);

#endif
