#include "scanner.h"
#include "parser_type.h"
#include "parser_priv.h"
# include <stdio.h>		// DEBUG
# include "logs.h"		// DEBUG
# include <assert.h>	// DEBUG

t_error	parser_read_heredoc(t_parser *parser)
{
	assert(parser != NULL);
	if (parser->must_read_heredoc == false
		|| parser->lookahead_raw_symbol != SYM_NEWLINE)
		return (error(ERR_NO));
	parser->must_read_heredoc = false;
#ifdef DEBUG_PARSING
	fprintf(stderr, "[PARSER] %sscanner_heredoc_read()%s\n", YELLOW, NC);
#endif
	return (scanner_heredoc_read());
}
