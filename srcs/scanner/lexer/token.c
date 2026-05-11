/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:59:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/10 14:55:37 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../_scanner.h"

void	free_token(t_token **token_ptr)
{
	if (token_ptr == NULL)
		return ;
	buff_free(&(*token_ptr)->value);
	**token_ptr = (t_token){0};
	free(*token_ptr);
	*token_ptr = NULL;
}

char	*DEBUG_token_type_stringify(t_token_type type)
{
	if (type == TOKEN       ) return (str_join("", "TOKEN"			));
	if (type == NEWLINE     ) return (str_join("", "NEWLINE"		));
	if (type == SCOLON      ) return (str_join("", "SCOLON"			));
	if (type == AMPERSAND   ) return (str_join("", "AMPERSAND"		));
	if (type == DSEMI       ) return (str_join("", "DSEMI"			));
	if (type == SEMI_AND    ) return (str_join("", "SEMI_AND"		));
	if (type == AND_IF      ) return (str_join("", "AND_IF"			));
	if (type == OR_IF       ) return (str_join("", "OR_IF"			));
	if (type == PIPE        ) return (str_join("", "PIPE"			));
	if (type == LPARENTHESIS) return (str_join("", "LPARENTHESIS"	));
	if (type == RPARENTHESIS) return (str_join("", "RPARENTHESIS"	));
	if (type == EOF         ) return (str_join("", "EOF"			));
	if (type == IO_NUMBER   ) return (str_join("", "IO_NUMBER"		));
	if (type == LESSAND     ) return (str_join("", "LESSAND"		));
	if (type == GREATAND    ) return (str_join("", "GREATAND"		));
	if (type == LESS        ) return (str_join("", "LESS"			));
	if (type == GREAT       ) return (str_join("", "GREAT"			));
	if (type == CLOBBER     ) return (str_join("", "CLOBBER"		));
	if (type == LESSGREAT   ) return (str_join("", "LESSGREAT"		));
	if (type == DGREAT      ) return (str_join("", "DGREAT"			));
	if (type == DLESS       ) return (str_join("", "DLESS"			));
	if (type == DLESSDASH   ) return (str_join("", "DLESSDASH"		));
	return (NULL);
}

bool	is_blank(t_lexer *lexer, size_t i)
{
	char	*input_ptr;

	input_ptr = lexer->input + i;
	return (input_ptr[0] == ' ' || input_ptr[0] == '\t');
}

t_token	*create_operator_token(t_operator_args args, size_t i)
{
	char *io_number_str;
	
	if (args.type != IO_NUMBER)
		return (create_token(NULL, i, args.type));
	else
	{
		io_number_str = ft_itoa(args.value);
		if (io_number_str == NULL)
			return (NULL);
		return (create_token(io_number_str, i, args.type));
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
