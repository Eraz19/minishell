#include "error.h"
#include "cst_type.h"
#include "ast_type.h"
#include "converter_priv.h"
#include "builder.h"

static inline t_error	convert_complete_commands(
	t_parser *parser,
	t_cst_node *complete_commands,
	t_ast_root *out)
{
	t_cst_node	*first_node;
	t_error		err;

	first_node = complete_commands->children[0];
	if (complete_commands->child_count == 1)
		return (convert_list_add(parser, first_node, out));
	err = convert_complete_commands(parser, first_node, out);
	if (err.type)
		return (err);
	return (convert_list_add(parser, complete_commands->children[2], out));
}

t_error	convert_cst_to_ast(
	t_parser *parser,
	t_cst_node *cst_root,
	t_ast_root *ast_root)
{
	t_cst_node	*node;
	t_error		err;

	ast_root_init(ast_root);
	node = cst_root;
	if (node->symbol == SYM_start)
		node = node->children[0];
	if (node->symbol == SYM_program)
	{
		if (node->child_count < 2)
			return (error(ERR_NO));
		node = node->children[1];
	}
	if (node->symbol == SYM_complete_commands)
		err = convert_complete_commands(parser, node, ast_root);
	else if (node->symbol == SYM_complete_command)
		err = convert_list_add(parser, node, ast_root);
	else
		return (error(ERR_INCOHERENT_STATE));
	if (err.type)
		ast_root_free(ast_root);
	return (err);
}
