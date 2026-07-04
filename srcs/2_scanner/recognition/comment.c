#include "scanner_recognition_.h"

bool	is_comment(t_lexer *lexer)
{
	return (lexer->input->str.data[lexer->input->i] == '#');
}

void	lexer_rule_comment(t_lexer *lexer)
{
	while (lexer->input->str.data[lexer->input->i] != '\0' &&
		lexer->input->str.data[lexer->input->i] != '\n')
		lexer->input->i++;
}
