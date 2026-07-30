#include "token_recognition_context.h"
#include "token_recognition_context_scan.h"

t_error	scan_context(t_token_recognition_context args)
{
	char		*str;
	t_context	context;

	scan_context_start(args);
	while (args.lexer->err.type == ERR_NO)
	{
		str = args.lexer->input->str.data + args.lexer->input->i;
		if (args.is_end != NULL && args.is_end(*str, args.unescaped_args))
			return (scan_context_end(args));
		else if (*str == '\\')
			args.escape(args.lexer);
		else if (args.quoting != NULL && args.is_quoting(str, &context))
			args.quoting(args.lexer, context);
		else if (args.expansion != NULL && args.is_expansion(str, &context))
			args.expansion(args.lexer, context);
		else
			args.unescaped(args.lexer, args.unescaped_args);
	}
	return (args.lexer->err);
}
