#include "shell.h"
#include "heredoc.h"
#include "heredoc_body.h"

t_error	heredoc_read_body(t_lexer *lexer, t_string *out, t_token *delim, bool strip)
{
	t_body	body;

	body_init(&body);
	if (body_load(&body, lexer, delim, strip).type)
		return (lexer->err = body.err, body_free(&body), lexer->err);
	lexer->err = scan_input_for_heredoc_body(&body);
	if (lexer->err.type && lexer->err.type != ERR_NO_DELIM)
		return (body_free(&body), lexer->err);
	if (!string_dup(out, &body.content))
		return (lexer->err = error_sys(), body_free(&body), lexer->err);
	if (lexer->input != NULL)
	{
		if (body.i < lexer->input->str.len)
			lexer->input->i = body.i;
		else
			lexer->input->i = lexer->input->str.len;
	}
	return (lexer->err = body.err, body_free(&body), lexer->err);
}

t_error	heredoc_lex_body(t_context_stack *stack_out, t_ast_vector *vec_out, t_string *body)
{
	t_error	err;
	t_token	token;
	t_lexer	*lexer;

	err = shell_get_new_lexer(&lexer, SCAN_MODE_STRING, body->data);
	if (err.type)
		return (err);
	bind_lexer_token(lexer, &token);
	if (scan_heredoc_body_context(lexer, &token, body).type)
	{
		token_free(&token);
		return (err = lexer->err, shell_destroy_last_instance(), err);
	}
	string_free(body);
	vector_take(stack_out, &token.contexts);
	vector_take(vec_out, &token.ast_vector);
	string_take_string(body, &token.value);
	return (token_free(&token), shell_destroy_last_instance());
}
