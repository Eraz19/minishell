#ifndef PARSER_H
# define PARSER_H

# include "parser_type.h"
# include "lr_machine_type.h"

void	parser_init(t_parser *parser);
t_error	parser_reset(t_parser *parser);
t_error	parser_build_qualifiers_table(t_parser *parser, t_lr_machine *machine);
t_error	parser_build_cst(t_parser *parser, t_lr_machine *machine);
t_error	parser_store_cst(t_parser *parser, t_parser_stack_item *main_item);
t_error	parser_reset(t_parser *parser);
void	parser_free(t_parser *parser);

// @ret ERR_PARSER_INVALID_STATE / ERR_PARSER_EMPTY_GOTO / ERR_LIBC
t_error	parser_can_next_token_be_a_cmd_name_or_word(
	t_parser *parser,
	t_lr_machine *machine,
	bool *dst);

#endif
