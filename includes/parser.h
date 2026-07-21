#ifndef PARSER_H
# define PARSER_H

# include "parser_type.h"
# include "token.h"
# include "ast.h"

// Life cycle

void	parser_init(t_parser *parser);
t_error	parser_load(
			t_parser *parser,
			t_scanner *parent_scanner,
			t_scan_mode mode);
void	parser_clear(t_parser *parser);
void	parser_free(t_parser *parser);

// Ops

t_error	parser_get_ast(t_parser *parser, t_ast_root *dst_ast);
t_error	parser_store_cst(t_parser *parser, t_parser_item *main_item);
t_token	*parser_get_token(const t_parser *parser, size_t index);
void	parser_take_token(t_parser *parser, size_t index, t_token *dst);

// @ret ERR_PARSER_INVALID_STATE / ERR_PARSER_EMPTY_GOTO / ERR_LIBC
t_error	parser_can_next_token_be_a_cmd_name_or_word(const t_parser *parser, bool *dst);

#endif
