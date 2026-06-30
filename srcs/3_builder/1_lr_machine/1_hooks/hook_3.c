#include "parser.h"
#include "scanner.h"
#include "cst.h"
#include <stdlib.h>
# include <stdio.h>	// DEBUG
# include "logs.h"	// DEBUG
# include <assert.h>

static void	free_buff_and_ptr(void *buff_ptr)
{
	t_buff	*buff;

	assert(buff_ptr != NULL);
	buff = (t_buff *)buff_ptr;
	buff_free(buff);
	free(buff);
}

t_error	hook_3(
	t_parser *parser,
	t_parser_stack_item *rhs,
	size_t len,
	t_parser_stack_item *lhs)
{
	t_token			*delim;
	t_heredoc_mode	mode;
	t_string		*path;
	t_error			err;

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
#ifdef DEBUG_PARSING
	fprintf(stderr, "[PARSER] %sscanner_report_io_here(%p, %s%s%s, %i)%s\n", YELLOW, &path, BLUE, delim->value.data, YELLOW, (int)mode, NC);
#endif
	err = scanner_report_io_here(path, delim, mode);
	if (err.type)
		return (err);
	cst_node_set_data(lhs->cst_node, path, free_buff_and_ptr);
	parser->must_read_heredoc = true;
	return (err);
}
