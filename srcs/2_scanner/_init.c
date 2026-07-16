#include "scanner.h"
#include "scanner_.h"

t_error	scanner_init(t_scanner *scanner)
{
	*scanner = (t_scanner){0};
	lexer_init(&scanner->lexer);
	return (error(ERR_NO));
}

void	scanner_free(t_scanner *scanner)
{
	lexer_free(&scanner->lexer);
	*scanner = (t_scanner){0};
}

t_error	scanner_load(t_scanner *scanner, const char *source)
{
	t_error	err;

	scanner->mode = INPUT_MODE_NONE;
	err = input_mode_set(&scanner->mode);
	if (err.type != ERR_NO)
		return (scanner_error_qualify(err, false));
	if (scanner->mode == INPUT_MODE_STRING || scanner->mode == INPUT_MODE_FILE)
		scanner->source = source;
	return (scanner->err);
}

void	scanner_clear(t_scanner *scanner)
{
	lexer_clear(&scanner->lexer);
}

void	scanner_init_subshell(t_scanner *scanner)
{
	scanner->mode = INPUT_MODE_STDIN_PIPE;
}
