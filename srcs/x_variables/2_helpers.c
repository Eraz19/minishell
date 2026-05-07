#include "libft.h"
#include "variable.h"
#include <stdlib.h>

bool	var_name_is_valid(const char *name)
{
	size_t	i;

	if (!name || !name[0])
		return (false);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (false);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	var_find(const t_var_list *variables, const char *var_name, size_t *res)
{
	size_t	i;
	size_t	len;
	t_var	*curr;

	len = 0;
	while (var_name[len] != '\0')
		len++;
	i = 0;
	while (i < variables->len)
	{
		curr = &((t_var *)variables->data)[i];
		if (str_ncmp(var_name, curr->name, len + 1) == 0)
		{
			*res = i;
			return (true);
		}
		i++;
	}
	return (false);
}

t_error	var_split(const char *src, char **dst_name, char **dst_value)
{
	size_t	len;

	if (!src || !dst_name || !dst_value)
		return (ERR_INVALID_POINTER);
	*dst_name = NULL;
	*dst_value = NULL;
	len = 0;
	while (src[len] && src[len] != '=')
		len++;
	if (src[len] == '\0')
		return (ERR_VAR_MISSING_EQUAL);
	*dst_name = malloc(len + 1);
	if (!*dst_name)
		return (ERR_OUT_OF_MEMORY);
	str_lcpy(*dst_name, src, len + 1);
	src += len + 1;
	len = 0;
	while (src[len])
		len ++;
	*dst_value = malloc(len + 1);
	if (!*dst_value)
		return (free(*dst_name), *dst_name = NULL, ERR_OUT_OF_MEMORY);
	str_lcpy(*dst_value, src, len + 1);
	return (ERR_NO);
}

t_error	var_update_value(t_var *var, const char *value)
{
	char	*new_value;

	new_value = str_dup(value);
	if (!new_value)
		return (ERR_OUT_OF_MEMORY);
	free(var->value);
	var->value = new_value;
	return (ERR_NO);
}
