#include "error.h"
#include "parser_type.h"
#include "ast_type.h"
#include "converter_priv.h"
# include <assert.h>	// DEBUG

static inline t_error	add_to_list(
							const t_parser *parser,
							const t_cst_node *compound_list,
							t_vector *out)
{
	t_ast_list	list;
	t_error		err;

	err = convert_list(parser, compound_list, &list);
	if (err.type)
		return (err);
	if (!vector_push(out, &list))
		return (err = error_sys(), ast_list_free(&list), err);
	return (error(ERR_NO));
}

static inline t_error	parse_rec(
							const t_parser *parser,
							const t_cst_node *node,
							t_ast_if *out)
{
	t_error	err;

	if (node->child_count == 2)
	{
		out->has_else = true;
		return (convert_list(parser, node->children[1], &out->else_body));
	}
	err = add_to_list(parser, node->children[1], &out->conditions);
	if (err.type == ERR_NO)
		err = add_to_list(parser, node->children[3], &out->bodies);
	if (err.type)
		return (err);
	if (node->child_count >= 5 && node->children[4]->symbol == SYM_else_part)
		return (parse_rec(parser, node->children[4], out));
	return (err);
}

/*
if_clause        : If compound_list Then compound_list else_part Fi
                 | If compound_list Then compound_list           Fi
                 ;
else_part        : Elif compound_list Then compound_list
                 | Elif compound_list Then compound_list else_part
                 | Else compound_list
                 ;
*/
t_error	convert_if(
			const t_parser *parser,
			const t_cst_node *if_clause,
			t_ast_if *out)
{
	t_error		err;

	assert(parser != NULL);
	assert(if_clause != NULL);
	assert(out != NULL);
	ast_if_init(out);
	err = parse_rec(parser, if_clause, out);
	if (err.type)
		ast_if_free(out);
	return (err);
}
