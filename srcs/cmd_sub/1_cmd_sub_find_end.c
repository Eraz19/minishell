#include "cmd_sub.h"
#include "ast.h"
#include "parser.h"
#include "shell.h"
# include <stdio.h>
# include "logs.h"

t_error	cmd_sub_find_end(ssize_t *out_closing_token_id, t_ast_vector *ast_vector)
{
	t_ast_root	ast_root;
	t_parser	*parser;
	t_error		err;

	fprintf(stderr, YELLOW "################# CMD SUB PARSING ################\n" NC);
	err = shell_get_new_parser(&parser, SCAN_MODE_CMD_SUB);
	if (err.type)
	{
		fprintf(stderr, YELLOW "##################################################\n" NC);
		return (err);
	}
	parser->search_cmd_sub_end = true;
	err = parser_get_ast(parser, &ast_root);
	fprintf(stderr, YELLOW "[PARSER] cmd sub end found at index %zu\n" NC, parser->cmd_sub_end_index);
	if (err.type == ERR_NO)
	{
		*out_closing_token_id = parser->cmd_sub_end_index;
		err = ast_vector_push(ast_vector, &ast_root);
		if (err.type)
			ast_root_free(&ast_root);
	}
	shell_destroy_last_instance();
	fprintf(stderr, YELLOW "##################################################\n" NC);
	return (err);
}
