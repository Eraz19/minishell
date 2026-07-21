#include "scanner.h"
#include "scanner_.h"
#include "reader_.h"
#include <readline/readline.h>

t_error	scanner_init(t_scanner *scanner, t_parser *parser, t_scan_mode mode)
{
	t_error	err;

	*scanner = (t_scanner){0};
	scanner->parser = parser;
	lexer_init(&scanner->lexer, scanner);
	if (mode == SCAN_MODE_AUTO)
	{
		err = scan_mode_set(&scanner->mode);
		if (err.type)
			return (err);
	}
	else
		scanner->mode = mode;
	return (error(ERR_NO));
}

void	scanner_init_subshell(t_scanner *scanner)
{
	if (scanner->mode == SCAN_MODE_STDIN_TTY)
		scanner->mode = SCAN_MODE_STDIN_PIPE;
}

t_error	scanner_load(t_scanner *scanner, const char *source)
{
	t_error	err;

	rl_catch_signals = 0;
	rl_getc_function = reader_rl_getc;
	scanner->mode = SCAN_MODE_NONE;
	err = scan_mode_set(&scanner->mode);
	if (err.type != ERR_NO)
		return (scanner->err = scanner_error_qualify(err, false));
	if (scanner->mode == SCAN_MODE_STRING || scanner->mode == SCAN_MODE_FILE)
		scanner->source = source;
	return (scanner->err);
}

void	scanner_clear(t_scanner *scanner)
{
	lexer_clear(&scanner->lexer);
}

void	scanner_free(t_scanner *scanner)
{
	lexer_free(&scanner->lexer);
	*scanner = (t_scanner){0};
}
