#include "libft.h"
#include "alias.h"
#include "alias_stack_.h"

void	alias_init(t_alias *alias)
{
	*alias = (t_alias){0};
	alias_stack_init(&alias->stack);
	hashmap_init(&alias->map, 0, free_char_ptr_void);
}

void	alias_free(t_alias *alias)
{
	alias_stack_free(&alias->stack);
	hashmap_free(&alias->map);
	*alias = (t_alias){0};
}
