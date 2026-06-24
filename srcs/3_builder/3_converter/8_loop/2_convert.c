#include "error.h"
#include "parser_type.h"
#include "ast_type.h"
#include "converter_priv.h"

/*
while_clause     : While compound_list do_group
                 ;
until_clause     : Until compound_list do_group
                 ;
do_group         : Do compound_list Done
                 ;
*/
t_error	convert_loop(
	t_parser *parser,
	t_cst_node *loop,
	t_ast_loop *out)
{
	t_error		err;

	ast_loop_init(out);
	if (loop->children[0]->symbol == SYM_While)
		out->condition_must_be_true = true;
	err = convert_list(parser, loop->children[1], &out->condition);
	if (err.type == ERR_NO)
		err = convert_list(parser, loop->children[2]->children[1], &out->body);
	if (err.type)
		ast_loop_free(out);
	return (err);
}
