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

static inline t_error	scanner_load_cmd_sub(t_scanner *scanner)
{
	if (scanner->mode != SCAN_MODE_CMD_SUB)
		return (error(ERR_NO));
	if (scanner->parent_scanner->mode != SCAN_MODE_STDIN
		&& scanner->parent_scanner->mode != SCAN_MODE_CMD_SUB)
		return (scanner->mode = scanner->parent_scanner->mode, error(ERR_NO));
	return (scanner->err = lexer_input_stack_dup(
		&scanner->lexer.input_stack,
		&scanner->parent_scanner->lexer.input_stack));
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
	scanner->mode = mode;
	if (mode != SCAN_MODE_AUTO)
		return (scanner_load_cmd_sub(scanner));
	err = params_get_source(&source);
	if (err.type)
		return (scanner->err = scanner_error_qualify(err, false));
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
