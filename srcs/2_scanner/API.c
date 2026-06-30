#include "shell.h"
#include "reader_.h"
#include "heredoc.h"
#include "scanner.h"
#include "scanner_.h"

t_error	scanner_get_next_token(t_token *token)
{
	t_scanner	*state;

	state = shell_get_scanner();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (state->lexer.input_stack.len == 0 && scanner_read_input(state).type)
		return (state->err);
	if (lexer_get_next_token(&state->lexer, token,
			scanner_lexer_rules(state)).type)
		return (state->err = state->lexer.err, state->err);
	if (token->type == TOKEN_TOKEN)
		return (scanner_alias_expand(state, token));
	return (state->err);
}
t_error	scanner_report_io_here(
			t_string *out_path,
			t_token *delim,
			t_heredoc_mode mode)
{
	t_scanner	*state;

	state = shell_get_scanner();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	state->err = heredoc_register(out_path, delim, mode);
	return (state->err);
}

t_error	scanner_heredoc_read(void)
{
	t_lexer_input_stack_item	*item;
	t_scanner					*state;

	state = shell_get_scanner();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (state->lexer.input == NULL)
	{
		state->err = heredoc_read_queue_heredoc_bodies(NULL, NULL);
	}
	else
	{
		item = state->lexer.input;
		state->err = heredoc_read_queue_heredoc_bodies(&item->str, &item->i);
	}
	return (state->err);
}

t_error	scanner_read_continuation(t_string *res)
{
	return (reader_continuation(res));
}
