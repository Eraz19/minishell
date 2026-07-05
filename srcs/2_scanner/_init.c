#include "shell.h"
#include "utils.h"
#include "scanner.h"

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

	scanner->mode = SCAN_NONE;
	err = scan_set_mode(&scanner->mode);
	if (err.type != ERR_NO)
		return (err);
	if (scanner->mode == SCAN_STRING || scanner->mode == SCAN_FILE)
		scanner->source = source;
	return (scanner->err);
}

t_error	scanner_reset(void)
{
	t_scanner	*scanner;

	scanner = shell_get_scanner();
	if (!scanner)
		return (error(ERR_SHELL_NOT_FOUND));
	lexer_reset(&scanner->lexer);
	return (error(ERR_NO));
}
