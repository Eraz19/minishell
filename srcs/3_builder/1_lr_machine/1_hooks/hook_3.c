#include "parser.h"
#include "scanner.h"
#include "cst.h"
#include "heredoc.h"
#include <stdlib.h>
# include <stdio.h>	// DEBUG
#ifdef DEBUG_PARSING
# include "logs.h"	// DEBUG
#endif
# include <assert.h>

static void	free_heredoc_cst_data(void *data)
{
	t_string	*heredoc_path;

	if (data == NULL)
		return ;
	heredoc_path = (t_string *)data;
#ifdef DEBUG_PARSING
	fprintf(stderr, "%s[%s()] unlinking heredoc...%s\n", YELLOW, __func__, NC);
#endif
	heredoc_unlink(heredoc_path->data);
	string_free(heredoc_path);
	free(heredoc_path);
}

t_error	hook_3(
			t_parser *parser,
			t_parser_stack_item *rhs,
			size_t len,
			t_parser_stack_item *lhs)
{
	t_token		*delim;
	t_here_mode	mode;
	t_string	*path;
	t_error		err;

	assert(parser != NULL);
	assert(lhs != NULL);
	assert(rhs != NULL);
	assert(len == 2);
	if (len != 2)
		return (error_print(error(ERR_HOOK_INVALID_RHS_LEN), __func__, NULL,
			"expected 2 received %i", (int)len));
	err = parser_get_token(__func__, parser, rhs->tokens_start_id + 1, &delim);
	if (err.type)
		return (err);
	if (rhs[0].symbol == SYM_DLESSDASH)
		mode = HEREDOC_MODE_TAB_STRIP;
	else
		mode = HEREDOC_MODE_NORMAL;
	path = malloc(sizeof(t_buff));
	if (!path)
		return (error_print(error_sys(), __func__,
			"unable to malloc heredoc path buff", NULL, NULL));
	err = scanner_report_io_here(path, delim, mode);
	if (err.type)
		return (err);
#ifdef DEBUG_PARSING
	fprintf(stderr, "[PARSER] %sscanner_report_io_here(%p, %s%s%s, %i) => '%s%s%s'%s\n",
		YELLOW, &path, BLUE, delim->value.data, YELLOW, (int)mode, BLUE, path->data, YELLOW, NC);
#endif
	cst_node_set_data(lhs->cst_node, path, free_heredoc_cst_data);
	parser->must_read_heredoc = true;
	return (err);
}
