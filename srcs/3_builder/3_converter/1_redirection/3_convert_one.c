#include "converter_priv.h"
#include "convert_io_priv.h"
#include <stdlib.h>
#include <unistd.h>
# include <assert.h>	// DEBUG

static inline t_error	convert_io_number(
							const t_parser *parser,
							const t_cst_node *io_number_node,
							t_ast_redirection *out)
{
	t_error	err;
	t_token	*token;

	err = converter_get_token(parser, io_number_node, 0, &token);
	if (err.type)
		return (err);
	if (!parse_int(token->value.data, &out->fd))
	{
		err = error(ERR_FD_INVALID);
		err = error_print(err, "converter", NULL, "%s", token->value.data);
		return (err);
	}
	// TODO: Disallow range of fd used for backuped fds
	return (err);
}

static inline t_error	convert_io_location(
							const t_parser *parser,
							const t_cst_node *io_location_node,
							t_ast_redirection *out)
{
	t_error	err;

	err = converter_get_token(parser, io_location_node, 0, &out->location);
	if (err.type)
		return (err);
	out->is_location = true;
	return (err);
}

/*
io_redirect      :             io_file
                 | IO_NUMBER   io_file
                 | IO_LOCATION io_file
                 |             io_here
                 | IO_NUMBER   io_here
                 | IO_LOCATION io_here
                 ;
io_file          : '<'       filename
                 | LESSAND   filename
                 | '>'       filename
                 | GREATAND  filename
                 | DGREAT    filename
                 | LESSGREAT filename
                 | CLOBBER   filename
                 ;
filename         : WORD
                 ;
io_here          : DLESS     here_end
                 | DLESSDASH here_end
                 ;
here_end         : WORD
                 ;
*/
t_error	convert_redirection(
			const t_parser *parser,
			const t_cst_node *io_redirect,
			t_ast_redirection *out)
{
	t_error		err;

	assert(parser != NULL);
	assert(io_redirect != NULL);
	assert(out != NULL);
	ast_redirection_init(out);
	if (io_redirect->child_count == 1)
	{
		out->fd = -1;
		return (convert_io_file_or_here(parser, io_redirect->children[0], out));
	}
	else if (io_redirect->children[0]->symbol == SYM_IO_NUMBER)
		err = convert_io_number(parser, io_redirect->children[0], out);
	else
		err = convert_io_location(parser, io_redirect->children[0], out);
	if (err.type)
		return (ast_redirection_free(out), err);
	return (convert_io_file_or_here(parser, io_redirect->children[1], out));
}

t_error	convert_redirection_add(
			const t_parser *parser,
			const t_cst_node *io_redirect,
			t_ast_redir_list *out)
{
	t_ast_redirection	redir;
	t_error				err;

	assert(parser != NULL);
	assert(io_redirect != NULL);
	assert(out != NULL);
	err = convert_redirection(parser, io_redirect, &redir);
	if (err.type)
		return (err);
	if (!vector_push(out, &redir))
		return (err = error_sys(), ast_redirection_free(&redir), err);
	return (error(ERR_NO));
}
