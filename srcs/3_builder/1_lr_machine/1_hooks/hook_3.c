#include "parser_type.h"
#include "scanner.h"
#include <stdlib.h>

static t_error	get_heredoc_delim(t_parser *parser, t_parser_stack_item *rhs, char **dst_str)
{
	t_token	*token;

	token = &((t_token *)parser->tokens.data)[rhs->tokens_start_id];
	*dst_str = buff_get_string(&token->value);
	if (!*dst_str)
		return (error_sys());
	return (error(ERR_NO));
}

# include <stdio.h>	// DEBUG
t_error	hook_3(t_parser_stack_item *rhs, size_t len, void *ctx)
{
	t_parser		*parser;
	char			*delim;
	t_heredoc_mode	mode;
	char			*path;	// TODO: store it inside cst node
	t_error			err;

	if (len != 2)
		return (error_print(error(ERR_HOOK_INVALID_RHS_LEN), __func__, NULL, "expected 2 received %i", (int)len));
	parser = (t_parser *)ctx;
	path = NULL;
	err = get_heredoc_delim(parser, &rhs[1], &delim);
	if (err.type != ERR_NO)
		return (error_print(err, __func__, "unable to get heredoc delimiter", NULL, NULL));
	if (rhs[0].symbol == SYM_DLESSDASH)
		mode = HEREDOC_MODE_TAB_STRIP;
	else
		mode = HEREDOC_MODE_NORMAL;
	printf("----------\n");
	printf ("[PARSER] [%s] scanner_report_io_here(%p, %s, %i)\n", __func__, &path, delim, (int)mode);
	printf("----------\n");
	err = scanner_report_io_here(&path, delim, mode);
	free(delim);
	free(path);	// TODO: remove it when cst_node is implemented (it will own it)
	return (err);
}
