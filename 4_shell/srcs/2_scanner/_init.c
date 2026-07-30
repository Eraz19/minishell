#include "reader.h"
#include "scanner.h"
#include <readline/readline.h>

void	scanner_init(t_scanner *scanner)
{
	*scanner = (t_scanner){0};
	lexer_init(&scanner->lexer, scanner);
}

void	scanner_load(t_scanner *scanner, t_scanner *parent_scanner, t_parser *parser, t_scan_mode mode)
{
	scanner->mode = mode;
	rl_catch_signals = 0;
	scanner->parser = parser;
	lexer_init(&scanner->lexer, scanner);
	rl_getc_function = reader_readline_hook;
	scanner->parent_scanner = parent_scanner;
}

void	scanner_free(t_scanner *scanner)
{
	scanner->source = NULL;
	scanner->parser = NULL;
	lexer_free(&scanner->lexer);
	scanner->mode = SCAN_MODE_NONE;
	scanner->parent_scanner = NULL;
	scanner->err.type = ERR_NO;
}

void	scanner_clear(t_scanner *scanner)
{
	lexer_clear(&scanner->lexer);
	scanner->err.type = ERR_NO;
}
