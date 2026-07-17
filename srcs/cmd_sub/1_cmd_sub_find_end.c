#include "cmd_sub.h"
#include "shell.h"
# include <stdio.h>
# include "logs.h"

t_error	cmd_sub_find_end(ssize_t *out_closing_token_id, t_ast_vector *ast_vector)
{
	t_shell				*shell;
	t_ast_root			ast_root;
	t_scanner			cmd_sub_scanner;
	t_cmd_sub_builder	cmd_sub_builder;
	t_error				err;

	fprintf(stderr, YELLOW "################# CMD SUB PARSING ################\n" NC);
	shell = shell_get();
	if (shell == NULL)
		return (error_print(error(ERR_INTERNAL),
					"unable to search command substitution end",
					"shell not found", NULL, NULL));
	err = scanner_cmd_sub_init(&shell->scanner, &cmd_sub_scanner);
	if (err.type)
		return (err);
	builder_cmd_sub_init(&shell->builder, &cmd_sub_builder, &cmd_sub_scanner);
	err = build_ast(&cmd_sub_builder.parser, cmd_sub_builder.lr_machine, &ast_root);
	if (err.type == ERR_NO)
	{
		*out_closing_token_id = cmd_sub_builder.parser.cmd_sub_end_index;
		fprintf(stderr, YELLOW "[PARSER] cmd sub end found at index %zu\n" NC, *out_closing_token_id);
	}
	scanner_cmd_sub_free(&cmd_sub_scanner);
	builder_cmd_sub_free(&cmd_sub_builder);
	if (err.type == ERR_NO)
	{
		err = ast_vector_push(ast_vector, &ast_root);
		if (err.type)
			ast_root_free(&ast_root);
	}
	fprintf(stderr, YELLOW "##################################################\n" NC);
	return (err);
}
