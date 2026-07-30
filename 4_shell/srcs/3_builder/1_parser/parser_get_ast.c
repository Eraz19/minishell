#include "parser.h"
#include "parser_priv.h"
#include "converter.h"
# include "debug.h"		// DEBUG
# include <assert.h>	// DEBUG

t_error	parser_get_ast(t_parser *parser, t_ast_root *dst_ast)
{
	t_error		err;

	assert(parser != NULL);
	assert(dst_ast != NULL);
	err = parser_build_cst(parser);
	if (err.type)
		return (err);
	dump_cst(parser->cst);
	err = convert_cst_to_ast(parser, parser->cst, dst_ast);
	if (err.type == ERR_NO)
		dump_ast(dst_ast);
	return (err);
}
