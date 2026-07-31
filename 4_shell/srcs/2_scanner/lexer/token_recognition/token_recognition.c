#include "token.h"
#include "scanner.h"
#include "token_recognition.h"
#include "token_recognition_priv.h"
#include "token_recognition_operator.h"

t_error	token_recognize_rules_dispatch(t_lexer *lexer)
{
	t_context	context;
	char		*current_char_ptr;

	current_char_ptr = lexer->input->str.data + lexer->input->i;
	if (is_context_none_ending(*current_char_ptr, NULL))
		return (recognize_token_input_end(lexer));
	else if (is_inside_operator(lexer))
		return (recognize_token_inside_operator(lexer));
	else if (is_quoting_context_start(current_char_ptr, &context))
		return (recognize_token_quoting_context(lexer, context));
	else if (is_expansion_context_start(current_char_ptr, &context))
		return (recognize_token_expansion_context(lexer, context));
	else if (is_new_operator(lexer))
		return (recognize_token_new_operator(lexer));
	else if (is_blank(*current_char_ptr))
		return (recognize_token_blank_delimiter(lexer));
	else if (is_inside_word(lexer))
		return (recognize_token_inside_word(lexer));
	else if (is_comment_start(lexer))
		return (recognize_token_escape_comment(lexer), lexer->err);
	else
		return (recognize_token_new_word(lexer));
}

t_error	emit_first_cmd_sub_token(t_lexer *lexer)
{
	if (token_recognition_consume(lexer, TOKEN_DOLPAREN, 2).type)
		return (lexer->err);
	token_recognition_delimit(lexer);
	return (lexer->err);
}

t_error	recognize_token(t_lexer *lexer, t_token *out)
{
	bind_lexer_token(lexer, out);
	if (lexer->input_stack.len == 1)
		lexer->token->index.start = (ssize_t)lexer->input->i;
	else
		lexer->token->index.start = lexer->last_index.start;
	if (lexer->scanner->mode == SCAN_MODE_CMD_SUB && !lexer->emited_token)
		return (emit_first_cmd_sub_token(lexer));
	lexer->emited_token = false;
	while (!lexer->emited_token)
	{
		if (token_recognize_rules_dispatch(lexer).type)
		{
			token_free(out);
			lexer_unbind_token(lexer);
			return (lexer->err);
		}
	}
	return (lexer->err);
}
