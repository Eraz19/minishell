#include <stdlib.h>
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
	t_key_value	*pair;
	t_alias		*alias;
	t_key_value	**pairs;

	alias = shell_get_alias();
	if (alias == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (name == NULL)
		return (alias_print_all(hashmap_get_all(&alias->map)), alias->err);
	else
	{
		pair = hashmap_get(&alias->map, name);
		if (pair == NULL)
			return (alias->err);
		pairs = malloc(sizeof(t_key_value *) * 2);
		if (pairs == NULL)
			return (alias->err = error_sys());
		pairs[0] = pair;
		pairs[1] = NULL;
		return (alias_print_all(pairs), alias->err);
	}
}

t_error	alias_remove(const char *name)
{
	t_alias	*alias;

	alias = shell_get_alias();
	if (alias == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (name == NULL)
		return (alias->err);
	return (hashmap_remove(&alias->map, name), alias->err);
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
		return (alias->err = error_sys()); // check in hashmap failure causes to check if it's error_sys
	return (alias->err);
}

t_error	alias_expand_token(t_string *expansion, const t_string *token_value)
{
	t_alias	*alias;
	char	*raw;

	alias = shell_get_alias();
	if (alias == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (is_token_alias_expandable(alias, token_value->data))
	{
		alias->err = alias_stack_push(&alias->stack, token_value->data);
		if (alias->err.type)
			return (alias->err);
		raw = hashmap_get(&alias->map, token_value->data)->value;
		if (raw == NULL)
			return (alias->err = error(ERR_INCOHERENT_STATE));
		if (!string_init(expansion, 0, raw, -1))
			return (error_sys());
		return (set_position_for_next_word(alias, expansion), alias->err);
	}
	return (alias->err);
}
