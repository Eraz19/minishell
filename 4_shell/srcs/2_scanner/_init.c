#include "reader.h"
#include "scanner.h"
#include "env.h"
#include <readline/readline.h>

void	scanner_init(t_scanner *scanner)
{
	*scanner = (t_scanner){0};
	lexer_init(&scanner->lexer, scanner);
}

t_error	scanner_load(t_scanner *scanner, t_scanner *parent_scanner, t_parser *parser, t_scan_mode mode)
{
	const t_string		*source;
	t_lexer_input_stack	*input_stack;
	t_lexer_input_stack	*parent_input_stack;

	scanner->mode = mode;
	rl_catch_signals = 0;
	scanner->parser = parser;
	lexer_init(&scanner->lexer, scanner);
	rl_getc_function = reader_readline_hook;
	scanner->parent_scanner = parent_scanner;
	scanner->err = env_get_source(&source);
	if (scanner->err.type)
		return (scanner->err);
	if (scanner->mode == SCAN_MODE_STRING || scanner->mode == SCAN_MODE_FILE)
		scanner->source = source->data;
	if (mode == SCAN_MODE_CMD_SUB)
	{
		input_stack = &scanner->lexer.input_stack;
		parent_input_stack = &parent_scanner->lexer.input_stack;
		scanner->err = lexer_input_stack_dup(input_stack, parent_input_stack);
	}
	return (scanner->err);
}

void	scanner_free(t_scanner *scanner)
{
	scanner->source = NULL;
	scanner->parser = NULL;
	lexer_free(&scanner->lexer);
	scanner->mode = SCAN_MODE_NONE;
	scanner->parent_scanner = NULL;
}

void	scanner_clear(t_scanner *scanner)
{
	lexer_clear(&scanner->lexer);
}
