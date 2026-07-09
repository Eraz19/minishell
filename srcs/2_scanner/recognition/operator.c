#include "scanner_recognition_.h"

static bool	is_next_char_redirection(t_lexer *lexer)
{
	return (lexer->input->str.data[lexer->input->i] == '>' ||
		lexer->input->str.data[lexer->input->i] == '<');
}

static bool	is_token_io_number(t_lexer *lexer)
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

static bool	is_token_io_location(t_lexer *lexer)
{
	const t_string	*value;

	value = &lexer->token->value;
	return (value->len >= 3 && value->data[0] == '{'
		&& value->data[value->len - 1] == '}');
}

bool	is_new_operator(t_lexer *lexer)
{
	return (!is_in_middle_of_operator(lexer) && is_operator_char(lexer));
}

t_error	lexer_rule_new_operator(t_lexer *lexer) // Rule 6
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
		return (lexer_delimit_token(lexer), lexer->err);
	}
	else
		return (lexer_add_char_into_token_operator(lexer), lexer->err);
}
