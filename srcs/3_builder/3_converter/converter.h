#ifndef CONVERTER_H
# define CONVERTER_H

# include "error.h"
# include "cst_type.h"
# include "ast.h"

t_error	convert_cst_to_ast(
	t_parser *parser,
	t_cst_node *cst_root,
	t_ast_root *ast_root);

#endif
