#include "token_recognition_priv.h"
#include "token_recognition_context.h"

bool	is_inside_word(t_lexer *lexer)
{
	return (lexer->token->type == TOKEN_TOKEN);
}

t_error	recognize_token_inside_word(t_lexer *lexer)  // Rule 8
{
	char	current_char;

	current_char = lexer->input->str.data[lexer->input->i]; 
	if (current_char == '\\')
		return (none_context_escape_rules(lexer));
	else
	{
		if (current_char == '=' && lexer->token->assignment_offset == -1)
			lexer->token->assignment_offset = (ssize_t)lexer->token->value.len;
		return (token_recognition_consume(lexer, TOKEN_TOKEN, 1));
	}
}
