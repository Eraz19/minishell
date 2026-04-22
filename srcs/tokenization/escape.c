#include <stdlib.h>
#include "_lexer.h"

t_token	*from_lexer_token(t_lexer_token **token_ptr)
{
	t_token			*res;
	t_lexer_token	*token;

	if (token_ptr == NULL || *token_ptr == NULL)
		return (NULL);
	res = malloc(sizeof(t_token));
	if (res == NULL)
		return (NULL);
	token = *token_ptr;
	res->start = token->start;
	res->value = token->value;
	res->
	return (res);
}

t_lexer_token	*pipe_token(t_raw_string_ptr start)
{
	t_lexer_token	*res;

	res = malloc(sizeof(t_lexer_token));
	if (res == NULL)
		return (NULL);
	res->type.control_ = PIPE;
	res->type.discriminant = CONTROL_;
	res->start = start;
	res->value = malloc(sizeof(char) * 2);
	if (res->value == NULL)
		return (free(res), NULL);
	res->value[0] = '|';
	res->value[1] = '\0';
	return (res);
}

int main (void)
{
	t_lexer_token	*token;
	t_token			*token2;

	token = pipe_token();
	tokens2 = from_lexer_token(&token);
}
