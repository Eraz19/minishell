t_error	alias_remove(const char *name)
{
	t_alias	*alias;

	alias = shell_get_alias();
	if (alias == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (name == NULL)
		return (error(ERR_NO));
	if (!hashmap_remove(&alias->map, name))
		return (error(ERR_ALIAS_NOT_FOUND));
	return (error(ERR_NO));
}

t_error	alias_add(const char *name, const char *value)
{
	t_alias	*alias;
	char	*value_copy;

	alias = shell_get_alias();
	if (alias == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (name == NULL)
		return (error(ERR_NO));
	if (value == NULL)
		value_copy = str_dup("");
	else
		value_copy = str_dup(value);
	if (value_copy == NULL)
		return (alias->err = error_sys());
	if (!hashmap_put(&alias->map, name, (void *)value_copy))
	{
		alias->err = error_sys();
		return (free(value_copy), alias->err);
	}
	return (error(ERR_NO));
}

bool	alias_is_valid_name(const char *name)
{
	size_t	i;

	if (name == NULL || *name == '\0')
		return (false);
	i = 0;
	while (name[i] != '\0')
	{
		if (!ft_isalnum(name[i]) &&
			name[i] != '_' &&
			name[i] != '!' &&
			name[i] != '%' &&
			name[i] != ',' &&
			name[i] != '-' &&
			name[i] != '@')
			return (false);
		i++;
	}
	return (true);
}

void	alias_init(t_alias *alias)
{
	*alias = (t_alias){0};
	alias_stack_init(&alias->stack);
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
