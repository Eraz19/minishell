#include "token_recognition_priv.h"
#include "token_recognition_context_scan.h"
#include "token_recognition_context_scan_priv.h"

t_error	scan_context_unescape(t_token_recognition_unescape args)
{
	t_token_type	type;

	type = args.lexer->token->type;
	if (args.lexer->input->str.data[args.lexer->input->i] == '\0')
		return (on_context_scan_EOI(args.lexer));
	else if (args.special_handler != NULL)
		return (args.special_handler(args.lexer, args.special_args));
	else
		return (token_recognition_consume(args.lexer, type, 1));
}
