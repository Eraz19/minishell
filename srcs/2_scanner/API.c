#include "shell.h"
#include "alias.h"
#include "scanner_.h"

t_error	scanner_get_next_token(t_token *token)
{
	t_scanner	*state;

	state = shell_get_scanner();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (state->lexer.reached_EOI)
	{
		state->err = alias_on_expansion_end();
		if (state->err.type)
			return (state->err);
	}
	if (state->lexer.input_stack.len == 0 && scanner_read_input(state).type)
		return (state->err);
	if (lexer_next_token(&state->lexer, token).type)
		return (state->err = state->lexer.err, state->err);
	else if (token->type == NEWLINE_ && state->heredoc.queue.len > 0)
		return (scanner_heredoc_store(state));
	else if (token->type == TOKEN)
		return (scanner_alias_expand(state, token));
	return (state->err);
}

t_error	scanner_report_io_here(char **path, char *delim, t_heredoc_mode mode)
{
	t_scanner	*state;

	state = shell_get_scanner();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (heredoc_add_to_queue(path, delim, mode).type)
		return (state->err = state->heredoc.err, state->err);
	return (state->err);
}

t_error	scanner_reset()
{
	t_scanner	*state;

	state = shell_get_scanner();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	//IMPLEMENT: reset the scanner state
	return (state->err);
}
