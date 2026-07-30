#include "lexer.h"

void	lexer_init(t_lexer *lexer, t_scanner *scanner)
{
	*lexer = (t_lexer){0};
	lexer->scanner = scanner;
	lexer->last_index.end = -1;
	lexer->last_index.start = -1;
	lexer->last_index.error = -1;
	lexer_input_stack_init(&lexer->input_stack);
}

void	lexer_free(t_lexer *lexer)
{
	lexer->input = NULL;
	lexer->token = NULL;
	lexer->scanner = NULL;
	lexer->last_index.end = -1;
	lexer->emited_token = false;
	lexer->last_index.start = -1;
	lexer->last_index.error = -1;
	lexer_input_stack_free(&lexer->input_stack);
}

void	lexer_clear(t_lexer *lexer)
{
	lexer->input = NULL;
	lexer->token = NULL;
	lexer->last_index.end = -1;
	lexer->emited_token = false;
	lexer->last_index.start = -1;
	lexer->last_index.error = -1;
	while (lexer->input_stack.len > 0)
		lexer_input_stack_pop(&lexer->input_stack);
}
