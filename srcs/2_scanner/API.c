#include "shell.h"
#include "reader_.h"
#include "heredoc.h"
#include "scanner_.h"

#include <stdio.h>
t_error	scanner_get_next_token(t_token *token)
{
	t_scanner	*state;

	state = shell_get_scanner();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (state->lexer.input_stack.len == 0 && scanner_read_input(state).type)
		return (state->err);
	if (state->lexer.input != NULL)
		printf("======> index %zu\n", state->lexer.input->i);
	if (lexer_next_token(&state->lexer, token).type)
		return (state->err = state->lexer.err, state->err);
	if (token->type == TOKEN_TOKEN)
		return (scanner_alias_expand(state, token));
	return (state->err);
}

#include <stdio.h>
t_error	scanner_report_io_here(t_buff *path, char *delim, t_heredoc_mode mode)
{
	bool		is_tty;
	t_scanner	*state;

	state = shell_get_scanner();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	printf("=====> heredoc_add_to_queue\n");
	is_tty = state->mode == SCAN_STDIN_TTY;
	state->err = heredoc_add_to_queue(path, delim, mode, is_tty);
	printf("=====> heredoc_add_to_queue done\n");
	return (state->err);
}

t_error	scanner_heredoc_read(void)
{
	t_input_lexer_stack_item	*item;
	t_scanner					*state;

	state = shell_get_scanner();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (state->lexer.input == NULL)
		state->err = heredoc_store_all(NULL, NULL);
	else
	{
		item = state->lexer.input;
		state->err = heredoc_store_all(item->str, &item->i);
	}
	return (state->err);
}

t_error	scanner_read_continuation(char **res)
{
	return (reader_continuation(res));
}
