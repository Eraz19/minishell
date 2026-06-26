#include "scanner.h"
#include "parser_type.h"

# include <stdio.h>	// DEBUG
# include "logs.h"	// DEBUG
t_error	parser_read_heredoc(t_parser *parser)
{
	t_error	err;

	if (parser->lookahead_raw_symbol != SYM_NEWLINE)
		return (error(ERR_NO));
	if (!parser->must_read_heredoc)
		return (error(ERR_NO));
	parser->must_read_heredoc = false;
	fprintf(stderr, "[PARSER] %sscanner_heredoc_read()%s\n", YELLOW, NC);
	err = scanner_heredoc_read();
	if (err.type == ERR_NO_DELIM)
	{
		err = error(ERR_REDIRECTION_FAILED);
		err = error_print(err, "parser", "missing here-document delimiter",
		NULL, NULL);	// TODO: print the missing delimiter
	}
	return (err);
}
