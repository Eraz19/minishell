#include "shell.h"
#include "heredoc.h"
#include "scanner_.h"

t_error	scanner_get_next_token(t_token *token)
{
	t_scanner	*state;

	state = shell_get_scanner();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (state->lexer.input_stack.len == 0 && scanner_read_input(state).type)
		return (state->err);
	if (lexer_next_token(&state->lexer, token).type)
		return (state->err = state->lexer.err, state->err);
	if (token->type == TOKEN_TOKEN)
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

#include <stdio.h>
t_error	scanner_heredoc_read(void)
{
	t_input_parser_stack_item	*item;
	t_scanner					*state;

	printf("=====> Enter heredoc read\n");
	state = shell_get_scanner();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	printf("=====> Scanner state obtained\n");
	printf("=====> Lexer input: %s\n", state->lexer.input ? state->lexer.input->str : "NULL");
	if (state->lexer.input != NULL)
	{
		item = state->lexer.input;
		state->err = heredoc_store_all(item->str, &item->i);
		if (state->err.type)
			return (state->err = state->heredoc.err);
	}
	return (state->err);
}
