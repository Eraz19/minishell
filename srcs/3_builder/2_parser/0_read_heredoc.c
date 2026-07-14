#include "heredoc.h"
#include "parser.h"
#include "parser_type.h"
#include "parser_priv.h"
#include "parser_here_stack.h"
# include <stdio.h>		// DEBUG
#ifdef DEBUG_PARSING
# include "logs.h"		// DEBUG
#endif
# include <assert.h>	// DEBUG

t_error	parser_read_heredoc(t_parser *parser)
{
	size_t		i;
	t_cst_node	*node;
	t_token		*delim;
	t_error		err;

	assert(parser != NULL);
	err = error(ERR_NO);
	i = 0;
	while (i < parser->here_stack.len)
	{
		node = parser_here_stack_first(&parser->here_stack);
		assert(node != NULL);
		delim = parser_get_token(parser, node->tokens_start_id + 1);
		err = heredoc_read(&node->heredoc_body, delim);
		if (err.type)
			return (err);
		i++;
	}
#ifdef DEBUG_PARSING
	fprintf(stderr, "[PARSER] %sheredoc_read(%p, %s%s%s)%s\n",
		YELLOW, &node->heredoc_body, BLUE, delim->value.data, YELLOW, NC);
#endif
	return (err);
}
