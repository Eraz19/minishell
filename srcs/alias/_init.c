#include <stdlib.h>
#include "shell.h"
#include "alias_stack_.h"
#include "_OLD_alias.h"

void	alias_init(t_alias *alias)
{
	*alias = (t_alias){0};
	alias_stack_init(&alias->stack);
	hashmap_init(&alias->map, 0, free);
}

void	alias_clear(t_alias *alias)
{
	alias_stack_clear(&alias->stack);
	hashmap_clear(&alias->map);
	alias->err = (t_error){0};
	alias->disable_position = false;
}

void	alias_free(t_alias *alias)
{
	alias_stack_free(&alias->stack);
	hashmap_free(&alias->map);
	*alias = (t_alias){0};
}

t_error	alias_remove_all(void)
{
	t_alias	*alias;

	alias = shell_get_alias();
	if (alias == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	hashmap_clear(&alias->map);
	return (error(ERR_NO));
}
