#include "alias.h"

void	alias_init(t_alias *alias)
{
	alias_table_init(&alias->table);
	alias_stack_init(&alias->stack);
	alias_forbidden_init(&alias->forbidden);
}

void	alias_clear_stack(t_alias *alias)
{
	alias_stack_clear(&alias->stack);
}

void	alias_clear_forbidden(t_alias *alias)
{
	alias_forbidden_clear(&alias->forbidden);
}

void	alias_clear(t_alias *alias)
{
	alias_table_clear(&alias->table);
	alias_stack_clear(&alias->stack);
	alias_forbidden_clear(&alias->forbidden);
}

void	alias_free(t_alias *alias)
{
	alias_table_free(&alias->table);
	alias_stack_free(&alias->stack);
	alias_forbidden_free(&alias->forbidden);
}
