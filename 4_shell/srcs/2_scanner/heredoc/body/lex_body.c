#include <stdlib.h>
#include "scanner.h"
#include "token_recognition.h"
#include "token_recognition_context.h"
#include "token_recognition_context_scan.h"

t_error	heredoc_body_context_escape_rules(t_lexer *lexer)
{
	t_token_recognition_escape	args;

	args.lexer = lexer;
	args.line_continuation = true;
	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.is_in_whitelist = is_in_context_heredoc_whitelist;
	return (scan_context_escape(args));
}

t_error	heredoc_body_context_unescape_rules(t_lexer *lexer, void *_)
{
	t_token_recognition_unescape	args;

	(void)_;
	args.lexer = lexer;
	args.special_args = NULL;
	args.special_handler = NULL;
	return (scan_context_unescape(args));
}

t_token_recognition_context	heredoc_body_context_rules(t_lexer *lexer)
{
	return ((t_token_recognition_context)
		{
			.lexer = lexer,
			.context_item = NULL,
			.opening_len = 0,
			.closing_len = 0,
			.quoting = NULL,
			.is_quoting = NULL,
			.expansion = recognize_token_expansion_context,
			.is_expansion = is_expansion_context_start,
			.unescaped_args = NULL,
			.unescaped = heredoc_body_context_unescape_rules,
			.escape = heredoc_body_context_escape_rules,
			.is_end = is_context_none_ending,
		}
	);
}

t_error	scan_heredoc_body_context(t_scanner *scanner, t_token *out)
{
	t_token_recognition_context	scan_args;
	t_context_stack_item		*heredoc_context;

	scan_args = heredoc_body_context_rules(&scanner->lexer);
	if (scanner_scan_word(scanner, out, scan_args).type)
		return (scanner->err);
	scanner->err = context_stack_item_init(&heredoc_context, CONTEXT_HEREDOC);
	if (scanner->err.type)
		return (scanner->err);
	if (out->value.len > 0)
		heredoc_context->end = out->value.len - 1;
	if (!vector_insert(&out->contexts, 0, &heredoc_context))
	{
		scanner->err = error_sys();
		free(heredoc_context);
	}
	return (scanner->err);
}
