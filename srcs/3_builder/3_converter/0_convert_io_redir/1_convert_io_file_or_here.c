#include "converter_priv.h"
#include "convert_io_priv.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG
#include "debug.h"

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
		return (error_print(error(ERR_INTERNAL), "builder", "converter",
					"unknown io operator", NULL, "%i (%s)",
					(int)symbol, symbol_to_string(symbol)));
	return (error(ERR_NO));
}

static inline bool	heredoc_should_expand(const t_token *delim_token)
{
	size_t	i;
	char	c;

	i = 0;
	while (i < delim_token->value.len)
	{
		c = delim_token->value.data[i];
		if (c == '\'' || c == '"' || c == '\\')
			return (false);
		i++;
	}
	return (true);
}

static inline void	convert_io_here(
						const t_parser *parser,
						const t_cst_node *io_here,
						t_ast_redirection *out)
{
	t_string			*heredoc_path;
	t_token				*delim;
	const t_cst_node	*here_end;

	heredoc_path = (t_string *)io_here->data;
	token_init(&out->word);
	string_take_string(&out->word.value, heredoc_path);
	here_end = io_here->children[1];
	delim = converter_get_token(parser, here_end, 0);
	out->expand_heredoc_body = heredoc_should_expand(delim);
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
			const t_cst_node *io_file_node,
			t_ast_redirection *out)
{
	t_symbol	symbol;
	t_cst_node	*filename_node;
	t_error		err;

	assert(parser != NULL);
	assert(io_file_node != NULL);
	assert(out != NULL);
	symbol = io_file_node->children[0]->symbol;
	err = convert_io_operator(symbol, &out->operation);
	if (err.type)
		return (ast_redirection_free(out), err);
	if (out->operation == AST_REDIR_HEREDOC)
		return (convert_io_here(parser, io_file_node, out), err);
	filename_node = io_file_node->children[1];
	converter_take_token(parser, filename_node, 0, &out->word);
	return (err);
}
