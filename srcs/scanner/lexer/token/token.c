/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:59:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/11 16:52:28 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "_token.h"
#include "../operator/_operator.h"

void	free_token(t_token **token_ptr)
{
	if (token_ptr == NULL)
		return ;
	buff_free(&(*token_ptr)->value);
	**token_ptr = (t_token){0};
	free(*token_ptr);
	*token_ptr = NULL;
}

bool	is_blank(t_lexer *lexer, size_t i)
{
	char	*input_ptr;

	input_ptr = lexer->input + i;
	return (input_ptr[0] == ' ' || input_ptr[0] == '\t');
}

t_token	*create_operator_token(t_operator_args *args, size_t i)
{
	char *io_number_str;
	
	if (args->type != IO_NUMBER)
		return (create_token(NULL, i, args->type));
	else
	{
		io_number_str = ft_itoa(args->value);
		if (io_number_str == NULL)
			return (NULL);
		return (create_token(io_number_str, i, args->type));
	}
}

t_token	*create_word_token(t_lexer *lexer, size_t i)
{
	char	*token_value;

	token_value = str_sub(lexer->input, (uint)lexer->i, i - lexer->i);
	if (token_value == NULL)
		return (NULL);
	return (create_token(token_value, lexer->i, TOKEN));
}

t_token	*create_token(char *content, size_t offset, t_token_type type)
{
	t_token	*res;

	res = malloc(sizeof(t_token));
	if (res == NULL)
		return (NULL);
	res->type = type;
	res->offset = offset;
	if (buff_init(&res->value, 0) == false)
		return (free(res), NULL);
	if (content != NULL)
		buff_append(&res->value, content, (long)str_len(content));
	return (res);
}
