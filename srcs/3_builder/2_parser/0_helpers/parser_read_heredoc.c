#include "scanner.h"
#include "parser.h"
#include "parser_type.h"
#include "parser_priv.h"
#include "parser_here_stack.h"
#ifdef DEBUG_PARSING
# include <stdio.h>	// DEBUG
# include "logs.h"	// DEBUG
# include "debug.h"	// DEBUG
#endif
# include <assert.h>	// DEBUG

t_error	parser_read_heredoc(t_parser *parser)
{
	size_t		i;
	t_cst_node	*io_here;
	t_token		*delim;
	bool		strip;
	t_error		err;

	assert(parser != NULL);
	err = error(ERR_NO);
	if (parser->lookahead_raw_symbol != SYM_NEWLINE)
		return (error(ERR_NO));
	i = 0;
	while (i < parser->here_stack.len)
	{
		io_here = parser_here_stack_get(&parser->here_stack, i);
		assert(io_here != NULL);
		assert(io_here->child_count == 2);
		delim = parser_get_token(parser, io_here->children[1]->tokens_start_id);
		strip = io_here->children[0]->symbol == SYM_DLESSDASH;
#ifdef DEBUG_PARSING
		fprintf(stderr, "%s[PARSER] scanner_read_heredoc(%p, %s%s%s, %s)%s\n",
			YELLOW, &io_here->heredoc_body, BLUE, delim->value.data, YELLOW, bool_to_string(strip), NC);
#endif
		err = scanner_read_heredoc(parser->scanner, &io_here->heredoc_body,
				delim, strip);
		if (err.type)
			return (err);
		i++;
	}
	vector_clear(&parser->here_stack, NULL);
	return (err);
}
