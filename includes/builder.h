#ifndef BUILDER_H
# define BUILDER_H

# include "error.h"
# include "lr_machine_type.h"
# include "parser_type.h"
# include "ast.h"

typedef struct s_builder
{
	t_lr_machine	lr_machine;
	t_parser		parser;
}	t_builder;

typedef struct s_cmd_sub_builder
{
	const t_lr_machine	*lr_machine;
	t_parser			parser;
}	t_cmd_sub_builder;

// Life cycle

// normal builder
void	builder_init(t_builder *builder, t_scanner *scanner);
void	builder_clear(t_builder *builder);
void	builder_free(t_builder *builder);

// cmd sub builder
void	builder_cmd_sub_init(
			const t_builder *main_builder,
			t_cmd_sub_builder *cmd_sub_builder,
			t_scanner *cmd_sub_scanner);
void	builder_cmd_sub_free(t_cmd_sub_builder *cmd_sub_builder);

// ops

t_error	builder_load(t_builder *builder);
t_error	build_ast(t_parser *parser, const t_lr_machine *machine, t_ast_root *dst_ast);
t_error	build_cmd_sub_ast(
			t_cmd_sub_builder *builder,
			ssize_t *out_closing_index,
			t_ast_root *dst_ast);

// @ret ERR_SHELL_NOT_FOUND
t_error	builder_can_next_word_be_a_cmd_name(t_parser *parser, bool *dst);

#endif
