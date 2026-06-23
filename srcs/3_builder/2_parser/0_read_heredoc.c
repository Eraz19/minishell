#include "scanner.h"
#include "parser_type.h"

# include <stdio.h>
# include "logs.h"
t_error	parser_read_heredoc(t_parser *parser)
{
	if (parser->lookahead_raw_symbol != SYM_NEWLINE)
		return (error(ERR_NO));
	if (!parser->must_read_heredoc)
		return (error(ERR_NO));
	parser->must_read_heredoc = false;
	fprintf(stderr, "[PARSER] %sscanner_heredoc_read()%s\n", YELLOW, NC);
	return (scanner_heredoc_read());
}
