#ifndef HOOKS_H
# define HOOKS_H

# include "parser.h"

bool	hook_2(t_stack_item *rhs, size_t rhs_len, void *ctx);
bool	hook_3(t_stack_item *rhs, size_t rhs_len, void *ctx); // trigger le switch en heredoc mode avec le delimiter still quoted
bool	hook_4(t_stack_item *rhs, size_t rhs_len, void *ctx);
bool	hook_5(t_stack_item *rhs, size_t rhs_len, void *ctx);
bool	hook_6(t_stack_item *rhs, size_t rhs_len, void *ctx);
bool	hook_7a(t_stack_item *rhs, size_t rhs_len, void *ctx);
bool	hook_7b(t_stack_item *rhs, size_t rhs_len, void *ctx);
bool	hook_8(t_stack_item *rhs, size_t rhs_len, void *ctx);
bool	hook_9(t_stack_item *rhs, size_t rhs_len, void *ctx);

#endif
