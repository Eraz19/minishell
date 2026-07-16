#ifndef PARSER_H
# define PARSER_H

# include "parser_type.h"
# include "lr_machine_type.h"
# include "token.h"

// Life cycle

void	parser_init(t_parser *parser);
void	parser_clear(t_parser *parser);
void	parser_free(t_parser *parser);

void	parser_cmd_sub_init(const t_parser *main_parser, t_parser *cmd_sub_parser);
void	parser_cmd_sub_free(t_parser *cmd_sub_parser);

// Ops

t_error	parser_build_qualifiers_table(
			t_parser *parser,
			const t_lr_machine *machine);
t_error	parser_build_cst(t_parser *parser, const t_lr_machine *machine);
t_error	parser_store_cst(t_parser *parser, t_parser_item *main_item);

t_token	*parser_get_token(const t_parser *parser, size_t index);

// TODO: old name = parser_get_token()
void	parser_take_token(t_parser *parser, size_t index, t_token *dst);

// @ret ERR_PARSER_INVALID_STATE / ERR_PARSER_EMPTY_GOTO / ERR_LIBC
t_error	parser_can_next_token_be_a_cmd_name_or_word(
			const t_parser *parser,
			const t_lr_machine *machine,
			bool *dst);

#endif
