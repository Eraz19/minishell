#include "cmd_sub.h"
#include "shell.h"
# include <assert.h>

t_error	cmd_sub_find_end(size_t *out_token_id)
{
	t_shell		*shell;
	t_scanner	cmd_sub_scanner;
	t_builder	cmd_sub_builder;
	t_ast_root	ast;
	t_error		err;

	shell = shell_get();
	if (shell == NULL)
		return (error_print(error(ERR_INTERNAL),
					"unable to search command substitution end",
					"shell not found", NULL, NULL));
	err = scanner_cmd_sub_init(&shell->scanner, &cmd_sub_scanner);
	if (err.type)
		return (err);
	err = builder_cmd_sub_init(&shell->builder, &cmd_sub_builder);
	if (err.type)
		return (scanner_free(&cmd_sub_scanner), err);
	err = build_ast(&ast);
	assert(ast.and_ors.cap == 0);
	assert(ast.asyncs.cap == 0);
	scanner_cmd_sub_free(&cmd_sub_scanner);
	builder_cmd_sub_free(&cmd_sub_builder);
	return (err);
}
