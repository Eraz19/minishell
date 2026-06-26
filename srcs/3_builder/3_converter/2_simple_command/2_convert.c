#include "error.h"
#include "parser_type.h"
#include "ast_type.h"
#include "converter_priv.h"

static inline t_error	add_token_to(
	t_parser *parser,
	t_cst_node *node,
	t_vector *out)
{
	t_token	*token;
	t_error	err;

	err = converter_get_token(parser, node, 0, &token);
	if (err.type)
		return (err);
	if (!vector_push(out, &token))
		return (error_sys());
	return (err);
}

static inline t_error	parse_rec(
	t_parser *parser,
	t_cst_node *node,
	t_ast_simple_command *out)
{
	size_t		i;
	t_cst_node	*child;
	t_error		err;

	err = error(ERR_NO);
	i = 0;
	while (i < node->child_count && err.type == ERR_NO)
	{
		child = node->children[i];
		if (child->symbol == SYM_io_redirect)
			err = convert_redirection_add(parser, child, &out->redirs);
		else if (child->symbol == SYM_cmd_name
			|| child->symbol == SYM_cmd_word
			|| child->symbol == SYM_WORD)
			err = add_token_to(parser, child, &out->words);
		else if (child->symbol == SYM_ASSIGNMENT_WORD)
			err = add_token_to(parser, child, &out->assignments);
		else
			err = parse_rec(parser, child, out);
		i++;
	}
	return (err);
}

/*
simple_command   : cmd_prefix cmd_word cmd_suffix
                 | cmd_prefix cmd_word
                 | cmd_prefix
                 | cmd_name cmd_suffix
                 | cmd_name
                 ;
cmd_prefix       :            io_redirect
                 | cmd_prefix io_redirect
                 |            ASSIGNMENT_WORD
                 | cmd_prefix ASSIGNMENT_WORD
                 ;
cmd_name         : WORD
                 ;
cmd_word         : WORD
                 ;
cmd_suffix       :            io_redirect
                 | cmd_suffix io_redirect
                 |            WORD
                 | cmd_suffix WORD
                 ;
*/
t_error	convert_simple_command(
	t_parser *parser,
	t_cst_node *simple_command,
	t_ast_simple_command *out)
{
	t_error		err;

	ast_simple_command_init(out);
	err = parse_rec(parser, simple_command, out);
	if (err.type)
		ast_simple_command_free(out);
	return (err);
}
