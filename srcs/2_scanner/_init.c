#include "scanner.h"
#include "scanner_.h"
#include "reader_.h"
#include "params.h"
#include <readline/readline.h>

void	scanner_init(t_scanner *scanner)
{
	scanner->err = error(ERR_NO);
	scanner->mode = SCAN_MODE_NONE;
	lexer_init(&scanner->lexer, scanner);
	scanner->source = NULL;
	scanner->parser = NULL;
	scanner->parent_scanner = NULL;
}

t_error	scanner_load(
			t_scanner *scanner,
			t_scanner *parent_scanner,
			t_parser *parser,
			t_scan_mode mode)
{
	const t_string	*source;
	t_error			err;

	*scanner = (t_scanner){0};
	scanner->parser = parser;
	scanner->parent_scanner = parent_scanner;
	lexer_init(&scanner->lexer, scanner);
	if (mode == SCAN_MODE_AUTO)
	{
		err = params_get_source(&source);
		rl_catch_signals = 0;
		rl_getc_function = reader_rl_getc;
		scanner->mode = SCAN_MODE_NONE;
		err = scan_mode_set(&scanner->mode);
		if (err.type != ERR_NO)
			return (scanner->err = scanner_error_qualify(err, false));
		if (scanner->mode == SCAN_MODE_STRING || scanner->mode == SCAN_MODE_FILE)
			scanner->source = source->data;
		if (err.type)
			return (scanner->err);
	}
	else
		scanner->mode = mode;
	return (error(ERR_NO));
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
