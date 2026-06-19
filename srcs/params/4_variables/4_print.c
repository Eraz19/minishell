#include "shell.h"
#include "variables_priv.h"
#include "posix_helpers.h"
#include "utils.h"
#include <unistd.h>
#include <stdlib.h>

// @ret ERR_LIBC
static t_error	var_print_one(const char *prefix, const t_var *var)
{
	t_buff	buff;
	char	*escaped_value;
	t_error	err;

	if (!buff_init(&buff, 0, prefix, -1))
		return (error_sys());
	if (!buff_append(&buff, var->name, -1))
		return (err = error_sys(), buff_free(&buff), err);
	if (var->value)
	{
		if (!buff_append(&buff, "=", -1))
			return (err = error_sys(), buff_free(&buff), err);
		err = serialize(var->value, &escaped_value);
		if (err.type != ERR_NO)
			return (buff_free(&buff), err);
		if (!buff_append(&buff, escaped_value, -1))
			return (err = error_sys(), free(escaped_value), buff_free(&buff),
				err);
		free(escaped_value);
	}
	if (!buff_append(&buff, "\n", -1))
		return (err = error_sys(), buff_free(&buff), err);
	err = posix_write(STDOUT_FILENO, buff.data, buff.len);
	return (buff_free(&buff), err);
}

t_error	var_print(t_var_print_mode mode)
{
	t_shell		*shell;
	t_var_list	*list;
	t_var		*var;
	size_t		i;
	t_error		err;

	shell = shell_get();
	if (!shell)
		return (error(ERR_SHELL_NOT_FOUND));
	list = &shell->params.variables;
	i = 0;
	err = error(ERR_NO);
	while (i < list->len)
	{
		var = &((t_var *)list->data)[i];
		if (mode == VAR_PRINT_EXPORT && var->export)
			err = var_print_one("export ", var);
		else if (mode == VAR_PRINT_READONLY && var->readonly)
			err = var_print_one("readonly ", var);
		if (err.type != ERR_NO)
			break ;
		i++;
	}
	return (err);
}
