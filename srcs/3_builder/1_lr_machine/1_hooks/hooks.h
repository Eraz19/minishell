#ifndef HOOKS_H
# define HOOKS_H

# include "builder.h"

t_error	hook_2(t_stack_item *rhs, size_t len, void *ctx);
t_error	hook_3(t_stack_item *rhs, size_t len, void *ctx); // trigger le switch en heredoc mode avec le delimiter still quoted
t_error	hook_4(t_stack_item *rhs, size_t len, void *ctx);
t_error	hook_5(t_stack_item *rhs, size_t len, void *ctx);
t_error	hook_6(t_stack_item *rhs, size_t len, void *ctx);
t_error	hook_7a(t_stack_item *rhs, size_t len, void *ctx);
t_error	hook_7b(t_stack_item *rhs, size_t len, void *ctx);
t_error	hook_8(t_stack_item *rhs, size_t len, void *ctx);
t_error	hook_9(t_stack_item *rhs, size_t len, void *ctx);

#endif
