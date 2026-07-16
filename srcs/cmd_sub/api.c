#include "cmd_sub.h"
#include "shell.h"
# include <assert.h>

t_error	cmd_sub_find_end(size_t *out_token_id, bool *found)
{
	t_shell				*shell;
	t_scanner			cmd_sub_scanner;
	t_cmd_sub_builder	cmd_sub_builder;
	t_error				err;

	shell = shell_get();
	if (shell == NULL)
		return (error_print(error(ERR_INTERNAL),
					"unable to search command substitution end",
					"shell not found", NULL, NULL));
	err = scanner_cmd_sub_init(&shell->scanner, &cmd_sub_scanner);
	if (err.type)
		return (err);
	builder_cmd_sub_init(&shell->builder, &cmd_sub_builder);
	err = builder_find_cmd_sub_end(&cmd_sub_builder, out_token_id, found);
	builder_cmd_sub_free(&cmd_sub_builder);
	scanner_cmd_sub_free(&cmd_sub_scanner);
	return (err);
}
