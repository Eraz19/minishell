#include "token_recognition_priv.h"
#include "token_recognition_operator.h"

bool	is_next_char_redirection(t_lexer *lexer)
{
	char	current_char;

	current_char = lexer->input->str.data[lexer->input->i];
	return (current_char == '>' || current_char == '<');
}

bool	is_token_io_number(t_lexer *lexer)
{
	size_t	i;

	i = 0;
	while (i < lexer->token->value.len)
	{
		if (!ft_isdigit(lexer->token->value.data[i]))
			return (false);
		i++;
	}
	return (lexer->token->value.len > 0);
}

bool	is_token_io_location(t_lexer *lexer)
{
	t_string	*value;
	char		last_char;
	char		first_char;

	value = &lexer->token->value;
	if (value->len >= 3)
	{
		first_char = value->data[0];
		last_char = value->data[value->len - 1];
		return (first_char == '{' && last_char == '}');
	}
	else
		return (false);
}

t_error	recognize_token_new_operator(t_lexer *lexer) // Rule 6
{
	if (lexer->token->type != TOKEN_NONE)
	{
		if (is_next_char_redirection(lexer))
		{
			if (is_token_io_number(lexer))
				lexer->token->type = TOKEN_IO_NUMBER;
			else if (is_token_io_location(lexer))
				lexer->token->type = TOKEN_IO_LOCATION;
		}
		return (token_recognition_delimit(lexer), lexer->err);
	}
	else
		return (token_recognition_consume_operator(lexer), lexer->err);
}
