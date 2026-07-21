#include "cmd_sub.h"
#include "ast.h"
#include "parser.h"
# include <stdio.h>
# include "logs.h"

t_error	cmd_sub_find_end(
			const t_scanner *scanner,
			ssize_t *out_closing_token_id,
			t_ast_vector *ast_vector)
{
	t_ast_root			ast_root;
	t_parser			cmd_sub_parser;
	t_error				err;

	fprintf(stderr, YELLOW "################# CMD SUB PARSING ################\n" NC);
	err = parser_cmd_sub_init(scanner->parser, &cmd_sub_parser);
	if (err.type)
	{
		fprintf(stderr, YELLOW "##################################################\n" NC);
		return (err);
	}
	err = parser_get_ast(&cmd_sub_parser, &ast_root);
	if (err.type == ERR_NO)
	{
		*out_closing_token_id = cmd_sub_parser.cmd_sub_end_index;
		fprintf(stderr, YELLOW "[PARSER] cmd sub end found at index %zu\n" NC, *out_closing_token_id);
	}
	parser_cmd_sub_free(&cmd_sub_parser);
	if (err.type == ERR_NO)
	{
		err = ast_vector_push(ast_vector, &ast_root);
		if (err.type)
			ast_root_free(&ast_root);
	}
	fprintf(stderr, YELLOW "##################################################\n" NC);
	return (err);
}
