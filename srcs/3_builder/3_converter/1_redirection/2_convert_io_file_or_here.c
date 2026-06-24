#include "converter_priv.h"

static inline t_error	convert_io_operator(
	t_symbol symbol,
	t_ast_redir_op *out_op)
{
	if (symbol == SYM_LESS)
		*out_op = AST_REDIR_READ;
	else if (symbol == SYM_DLESS || symbol == SYM_DLESSDASH)
		*out_op = AST_REDIR_HEREDOC;
	else if (symbol == SYM_LESSAND)
		*out_op = AST_REDIR_DUP_READ;
	else if (symbol == SYM_GREAT)
		*out_op = AST_REDIR_WRITE;
	else if (symbol == SYM_DGREAT)
		*out_op = AST_REDIR_APPEND;
	else if (symbol == SYM_GREATAND)
		*out_op = AST_REDIR_DUP_WRITE;
	else if (symbol == SYM_CLOBBER)
		*out_op = AST_REDIR_CLOBBER;
	else if (symbol == SYM_LESSGREAT)
		*out_op = AST_REDIR_READ_WRITE;
	else
		return (error(ERR_INCOHERENT_STATE));
	return (error(ERR_NO));
}

static inline bool	heredoc_should_expand(t_buff *token_buff)
{
	size_t	i;
	char	c;

	i = 0;
	while (i < token_buff->len)
	{
		c = ((char *)token_buff->data)[i];
		if (c == '\'' || c == '"' || c == '\\')
			return (false);
		i++;
	}
	return (true);
}

static inline t_error	convert_here_end(
	t_parser *parser,
	t_cst_node *here_end,
	t_ast_redirection *out)
{
	t_buff	delim;
	t_error	err;

	err = converter_dup_buff(parser, here_end, 0, &delim);
	if (err.type)
		return (ast_redirection_free(out), err);
	out->expand_heredoc_body = heredoc_should_expand(&delim);
	return (error(ERR_NO));
}

static inline t_error	convert_io_here(
	t_cst_node *io_here,
	t_ast_redirection *out)
{
	t_buff	*heredoc_path;

	heredoc_path = (t_buff *)io_here->data;
	if (!buff_dup_n(&out->word, heredoc_path, heredoc_path->len))
		return (ast_redirection_free(out), error_sys());
	return (error(ERR_NO));
}

/*
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
*/
t_error	convert_io_file_or_here(
	t_parser *parser,
	t_cst_node *io_file_node,
	t_ast_redirection *out)
{
	t_symbol	symbol;
	t_cst_node	*filename_node;
	t_error		err;

	symbol = io_file_node->children[0]->symbol;
	err = convert_io_operator(symbol, &out->operation);
	if (err.type)
		return (ast_redirection_free(out), err);
	if (out->operation == AST_REDIR_HEREDOC)
	{
		err = convert_io_here(io_file_node, out);
		if (err.type)
			return (err);
		return (convert_here_end(parser, io_file_node->children[1], out));
	}
	filename_node = io_file_node->children[1];
	err = converter_dup_buff(parser, filename_node, 0, &out->word);
	if (err.type)
		ast_redirection_free(out);
	return (err);
}
