#include "error.h"
#include "parser_type.h"
#include "ast.h"
#include "converter_priv.h"
# include <assert.h>	// DEBUG

static inline t_error	parse_rec(
							t_parser *parser,
							const t_cst_node *node,
							t_ast_scmd *out)
{
	t_cst_node	*child;
	size_t		i;
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
			err = converter_transfer_token(parser, child, 0, &out->words);
		else if (child->symbol == SYM_ASSIGNMENT_WORD)
			err = converter_transfer_token(parser, child, 0, &out->assignments);
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
			const t_cst_node *simple_command,
			t_ast_scmd *out)
{
	t_error		err;

	assert(parser != NULL);
	assert(simple_command != NULL);
	assert(out != NULL);
	ast_simple_command_init(out);
	err = parse_rec(parser, simple_command, out);
	if (err.type)
		ast_simple_command_free(out);
	return (err);
}
