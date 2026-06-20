#ifndef PARSER_H
# define PARSER_H

# include "builder.h"

void	parser_init(t_parser *parser);
t_error	parser_build_cst(t_parser *parser, t_lr_machine *machine);
void	parser_free(t_parser *parser);

#endif
