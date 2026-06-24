#ifndef CONVERT_IO_PRIV_H
# define CONVERT_IO_PRIV_H

# include "parser_type.h"
# include "ast_type.h"

t_error	convert_io_file_or_here(
	t_parser *parser,
	t_cst_node *io_file_node,
	t_ast_redirection *out);

#endif
