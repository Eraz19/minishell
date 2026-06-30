#include "scanner.h"
#include "parser_type.h"
#include "parser_priv.h"
# include <stdio.h>		// DEBUG
# include "logs.h"		// DEBUG
# include <assert.h>	// DEBUG

t_error	parser_read_heredoc(t_parser *parser)
{
	t_error	err;

	assert(parser != NULL);
	if (parser->must_read_heredoc == false
		|| parser->lookahead_raw_symbol != SYM_NEWLINE)
		return (error(ERR_NO));
	parser->must_read_heredoc = false;
#ifdef DEBUG_PARSING
	fprintf(stderr, "[PARSER] %sscanner_heredoc_read()%s\n", YELLOW, NC);
#endif
	err = scanner_heredoc_read();
	if (err.type == ERR_NO_DELIM)
		err = error_print(error(ERR_REDIRECTION_FAILED), "parser", NULL, NULL);
	return (err);
}
