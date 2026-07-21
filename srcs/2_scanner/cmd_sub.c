#include "scanner.h"
#include "scanner_.h"

t_error    scanner_cmd_sub_init(
				const t_scanner *main_scanner,
				t_scanner *cmd_sub_scanner,
				t_parser *cmd_sub_parser)
{
	t_error	err;

	err = scanner_init(cmd_sub_scanner, cmd_sub_parser, main_scanner->mode);
	if (err.type)
		return (cmd_sub_scanner->err = scanner_error_qualify(err, false));
	cmd_sub_scanner->mode = main_scanner->mode;
	cmd_sub_scanner->source = main_scanner->source;
	lexer_init(&cmd_sub_scanner->lexer, cmd_sub_scanner);
	err = lexer_input_stack_dup(
			&cmd_sub_scanner->lexer.input_stack,
			&main_scanner->lexer.input_stack);
	return (cmd_sub_scanner->err = scanner_error_qualify(err, false));
}

void    scanner_cmd_sub_free(t_scanner *cmd_sub_scanner)
{
	scanner_free(cmd_sub_scanner);
}
