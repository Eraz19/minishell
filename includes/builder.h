#ifndef BUILDER_H
# define BUILDER_H

# include "error.h"
# include "lr_machine_type.h"
# include "parser_type.h"

typedef struct s_ast_node
{
	// TODO
}	t_ast_node;

typedef struct s_converter
{
	// TODO
}	t_converter;

typedef struct s_builder
{
	t_lr_machine	lr_machine;
	t_parser		parser;
	t_converter		converter;
}	t_builder;

void	builder_init(t_builder *builder);
t_error	builder_load(t_builder *builder);
t_error	builder_get_ast(t_ast_node **dst_ast);
t_error	builder_reset(void);
void	builder_free(t_builder *builder);

// @ret ERR_SHELL_NOT_FOUND
t_error	builder_can_next_word_be_a_cmd_name(bool *dst);

#endif
