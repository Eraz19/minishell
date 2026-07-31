#include "cmd_sub.h"
#include "parser.h"
#include "shell.h"
#ifdef DEBUG_CMD_SUB
# include "logs.h"
#endif

t_error	cmd_sub_find_end(ssize_t *out_closing_token_id, t_ast_vector *ast_vector)
{
	t_ast_root	ast_root;
	t_parser	*parser;
	t_error		err;

#ifdef DEBUG_CMD_SUB
	fprintf(stderr, YELLOW "################# CMD SUB PARSING ################\n" NC);
#endif
	err = shell_get_new_parser(&parser, SCAN_MODE_CMD_SUB, NULL);
	if (err.type)
	{
#ifdef DEBUG_CMD_SUB
		fprintf(stderr, YELLOW "##################################################\n" NC);
#endif
		return (err);
	}
	parser->search_cmd_sub_end = true;
	err = parser_get_ast(parser, &ast_root);
#ifdef DEBUG_CMD_SUB
	fprintf(stderr, YELLOW "[PARSER] cmd sub end found at index %zu\n" NC, parser->cmd_sub_end_index);
#endif
	if (err.type == ERR_NO)
	{
		*out_closing_token_id = parser->cmd_sub_end_index;
		err = ast_vector_push(ast_vector, &ast_root);
		if (err.type)
			ast_root_free(&ast_root);
	}
	shell_destroy_last_instance();
#ifdef DEBUG_CMD_SUB
	fprintf(stderr, YELLOW "##################################################\n" NC);
#endif
	return (err);
}
