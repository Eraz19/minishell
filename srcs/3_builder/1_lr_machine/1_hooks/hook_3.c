#include "parser_type.h"
#include "scanner.h"
#include "cst.h"
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
# include "logs.h"	// DEBUG
t_error	hook_3(
	t_parser *parser,
	t_parser_stack_item *rhs,
	size_t len,
	t_parser_stack_item *lhs)
{
	char			*path;
	char			*delim;
	t_heredoc_mode	mode;
	t_error			err;

	if (len != 2)
		return (error_print(error(ERR_HOOK_INVALID_RHS_LEN), __func__, NULL, "expected 2 received %i", (int)len));
	err = get_heredoc_delim(parser, &rhs[1], &delim);
	if (err.type != ERR_NO)
		return (error_print(err, __func__, "unable to get heredoc delimiter", NULL, NULL));
	if (rhs[0].symbol == SYM_DLESSDASH)
		mode = HEREDOC_MODE_TAB_STRIP;
	else
		mode = HEREDOC_MODE_NORMAL;
	path = NULL;
	fprintf(stderr, "[PARSER] %sscanner_report_io_here(%p, %s%s%s, %i)%s\n", YELLOW, &path, BLUE, delim, YELLOW, (int)mode, NC);
	err = scanner_report_io_here(&path, delim, mode);
	if (err.type == ERR_NO)
	{
		cst_node_set_data(lhs->cst_node, path, free);
		parser->must_read_heredoc = true;
	}
	free(delim);
	return (err);
}
