#ifndef BUILDER_H
# define BUILDER_H

# include "error.h"
# include "lr_machine_type.h"
# include "parser_type.h"
# include "ast_type.h"

typedef struct s_builder
{
	t_lr_machine	lr_machine;
	t_parser		parser;
}	t_builder;

void	builder_init(t_builder *builder);
t_error	builder_load(t_builder *builder);
t_error	builder_reset(void);
void	builder_free(t_builder *builder);

t_error	builder_get_ast(t_ast_root *dst_ast);
void	ast_root_free(t_ast_root *root);

// @ret ERR_SHELL_NOT_FOUND
t_error	builder_can_next_word_be_a_cmd_name(bool *dst);

#endif
