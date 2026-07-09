#include <stdlib.h>
#include "libft.h"
#include "alias.h"
#include "shell.h"
#include "alias_.h"
#include "alias_stack_.h"

t_error	alias_on_expansion_end(void)
{
	t_alias	*alias;

	alias = shell_get_alias();
	if (alias == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (alias->stack.len == 0)
		return (alias->err);
	return (alias_stack_pop(&alias->stack), alias->err);
}

t_error	alias_print(const char *name)
{
	t_alias				*alias;
	const t_key_value	**pairs;

	alias = shell_get_alias();
	if (alias == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (name != NULL)
		return (alias_print_one(alias, name));
	pairs = hashmap_get_all(&alias->map);
	if (pairs == NULL)
		return (alias->err = error_sys());
	return (alias_print_all(pairs));
}

t_error	alias_remove(const char *name)
{
	t_alias	*alias;

	alias = shell_get_alias();
	if (alias == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (name == NULL)
		return (alias->err);
	if (!hashmap_remove(&alias->map, name))
		return (error(ERR_ALIAS_NOT_FOUND));
	return (alias->err);
}

t_error	alias_add(const char *name, const char *value)
{
	t_alias	*alias;
	char	*value_copy;

	alias = shell_get_alias();
	if (alias == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (name == NULL)
		return (alias->err);
	if (value == NULL)
		value_copy = str_dup("");
	else
		value_copy = str_dup(value);
	if (value_copy == NULL)
		return (alias->err = error_sys());
	if (!hashmap_put(&alias->map, name, (void *)value_copy))
		return (free(value_copy), alias->err = error_sys());
	return (alias->err);
}

t_error	alias_expand_token(t_string *expansion, const t_string *token_value)
{
	t_alias		*alias;
	const char	*raw;
	char		*name;

	alias = shell_get_alias();
	if (alias == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (!is_token_alias_expandable(alias, token_value->data))
		return (alias->err);
	name = str_dup(token_value->data);
	if (name == NULL)
		return (alias->err = error_sys());
	alias->err = alias_stack_push(&alias->stack, name);
	if (alias->err.type)
		return (free(name), alias->err);
	raw = hashmap_get(&alias->map, token_value->data);
	if (raw == NULL)
		return (alias_stack_pop(&alias->stack),
			alias->err = error(ERR_INCOHERENT_STATE));
	if (!string_init(expansion, 0, raw, -1))
		return (alias_stack_pop(&alias->stack), alias->err = error_sys());
	return (set_position_for_next_word(alias, expansion), alias->err);
}
