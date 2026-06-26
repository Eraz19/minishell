#include "converter_priv.h"
#include "convert_io_priv.h"
#include <stdlib.h>
#include <unistd.h>

static inline t_error	convert_io_number(
	t_parser *parser,
	t_cst_node *io_number_node,
	t_ast_redirection *out)
{
	t_error	err;
	char	*token_string;

	err = converter_get_string(parser, io_number_node, 0, &token_string);
	if (err.type)
		return (err);
	out->fd = ft_atoi(token_string);
	free(token_string);
	return (error(ERR_NO));
}

static inline t_error	convert_io_location(
	t_parser *parser,
	t_cst_node *io_location_node,
	t_ast_redirection *out)
{
	t_error	err;
	t_buff	*token_buff;
	char	*src;

	err = converter_get_buff(parser, io_location_node, 0, &token_buff);
	if (err.type)
		return (err);
	src = ((char *)token_buff->data) + 1;
	if (!buff_append(&out->location, src, (long)token_buff->len - 2))
		return (error_sys());
	out->is_location = true;
	return (error(ERR_NO));
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
	t_parser *parser,
	t_cst_node *io_redirect,
	t_ast_redirection *out)
{
	t_error		err;

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
	t_parser *parser,
	t_cst_node *io_redirect,
	t_ast_redir_list *out)
{
	t_ast_redirection	redir;
	t_error				err;

	err = convert_redirection(parser, io_redirect, &redir);
	if (err.type)
		return (err);
	if (!vector_push(out, &redir))
		return (ast_redirection_free(&redir), error_sys());
	return (error(ERR_NO));
}
