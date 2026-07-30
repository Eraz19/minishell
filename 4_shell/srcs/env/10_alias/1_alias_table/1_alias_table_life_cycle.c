#include "alias_table_internal.h"
#include <stdlib.h>

void	alias_free_value(t_string *value)
{
	string_free(value);
	free(value);
}


void	alias_free_value_void(void *value)
{
	alias_free_value(value);
}

void	alias_table_init(t_alias_table *table)
{
	(void)hashmap_init(table, 0, alias_free_value_void);
}

void	alias_table_clear(t_alias_table *table)
{
	hashmap_clear(table);
}

void	alias_table_free(t_alias_table *table)
{
	hashmap_free(table);
}
