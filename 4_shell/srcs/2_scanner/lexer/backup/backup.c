#include <stdlib.h>
#include "lexer_backup.h"

t_lexer_backup	lexer_backup(t_lexer *lexer)
{
	t_lexer_backup res;

    res.i = lexer->input->i;
    res.token_type = lexer->token->type;
    res.token_value_len = lexer->token->value.len;
    res.token_contexts_len = lexer->token->contexts.len;
	return (res);
}

t_error	lexer_restore(t_lexer *lexer, t_lexer_backup backup)
{
	t_context_stack_item	*item;

	while (lexer->token->contexts.len > backup.token_contexts_len)
	{
		context_stack_bpop(&lexer->token->contexts, &item);
		free(item);
	}
    lexer->input->i = backup.i;
    lexer->token->type = backup.token_type;
    lexer->token->value.len = backup.token_value_len;
	if (lexer->token->value.data != NULL)
		lexer->token->value.data[backup.token_value_len] = '\0';
	return (lexer->err);
}
