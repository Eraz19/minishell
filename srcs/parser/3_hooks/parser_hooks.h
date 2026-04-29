#ifndef PARSER_HOOKS_H
# define PARSER_HOOKS_H

# include "parser.h"

bool	hook_2(t_stack_item *rhs, size_t rhs_len, void *ctx);
bool	hook_3(t_stack_item *rhs, size_t rhs_len, void *ctx);
bool	hook_4(t_stack_item *rhs, size_t rhs_len, void *ctx);
bool	hook_5(t_stack_item *rhs, size_t rhs_len, void *ctx);
bool	hook_6(t_stack_item *rhs, size_t rhs_len, void *ctx);
bool	hook_7a(t_stack_item *rhs, size_t rhs_len, void *ctx);
bool	hook_7b(t_stack_item *rhs, size_t rhs_len, void *ctx);
bool	hook_8(t_stack_item *rhs, size_t rhs_len, void *ctx);
bool	hook_9(t_stack_item *rhs, size_t rhs_len, void *ctx);
bool	hook_io_here(t_stack_item *rhs, size_t rhs_len, void *ctx);			// Set `parser.io_here_found` to true
bool	hook_switch_lexer(t_stack_item *rhs, size_t rhs_len, void *ctx);	// Trigger lexer heredoc mode then set `parser.io_here_found` to false

#endif
