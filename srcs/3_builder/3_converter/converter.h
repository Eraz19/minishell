#ifndef CONVERTER_H
# define CONVERTER_H

# include "error.h"
# include "cst_type.h"
# include "ast_type.h"

t_error	convert_cst_to_ast(t_cst_node *cst_root, t_ast_root *ast_root);

#endif
