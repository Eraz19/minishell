#include "scanner.h"
#include "scanner_.h"
#include "reader_.h"
#include "params.h"
#include <readline/readline.h>

static inline t_error	scanner_load(t_scanner *scanner)
{
	const t_string	*source;
	t_error			err;

	rl_catch_signals = 0;
	rl_getc_function = reader_rl_getc;
	scanner->mode = SCAN_MODE_NONE;
	err = scan_mode_set(&scanner->mode);
	if (err.type)
		return (scanner->err = scanner_error_qualify(err, false));
	if (scanner->mode == SCAN_MODE_STRING || scanner->mode == SCAN_MODE_FILE)
	{
		err = params_get_source(&source);
		if (err.type)
			return (scanner->err = scanner_error_qualify(err, false));
		scanner->source = source->data;
	}
	return (scanner->err);
}

t_error	scanner_init(t_scanner *scanner, t_parser *parser, t_scan_mode mode)
{
	t_error	err;

	*scanner = (t_scanner){0};
	scanner->parser = parser;
	lexer_init(&scanner->lexer, scanner);
	if (mode == SCAN_MODE_AUTO)
	{
		err = scanner_load(scanner);
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

void	scanner_clear(t_scanner *scanner)
{
	lexer_clear(&scanner->lexer);
}

void	scanner_free(t_scanner *scanner)
{
	lexer_free(&scanner->lexer);
	*scanner = (t_scanner){0};
}
