#include "lexer.h"
#include "scanner_priv.h"
#include "token_recognition_priv.h"
#include "token_recognition_context_scan.h"
#include "token_recognition_context_scan_priv.h"

t_error	on_context_scan_EOI(t_lexer *lexer)
{
	if (lexer->input_stack.len > 1)
		return (lexer_pop_alias(lexer));
	lexer->err = read_and_propagate_PS2(lexer->scanner);
	if (lexer->err.type == ERR_POSIX_SYNTAX || lexer->err.type == ERR_VEOF)
		return (error_unterminated_construct(lexer));
	return (lexer->err);
}

t_error	scan_context_end(t_token_recognition_context args)
{
	t_token_type	type;

	type = args.lexer->token->type;
	if (args.context_item != NULL)
		args.context_item->end = args.lexer->token->value.len;
	return (token_recognition_consume(args.lexer, type, args.closing_len));
}
