/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DEBUG.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 16:23:11 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/14 16:03:37 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "_token.h"

void	DEBUG_print_token(t_token *token)
{
	ft_printf("- TOKEN ----------------------\n");
	if (token == NULL)
		ft_printf("NO TOKEN\n");
	else
	{
		ft_printf("Type: %s\n", DEBUG_token_type_stringify(token->type));
		ft_printf("Offset: %d\n", (int)token->offset);
		ft_printf("Value: '%s'\n", buff_get_string(&token->value));
	}
	ft_printf("------------------------------\n");
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

bool	DEBUG_is_token_equal(t_token token1, t_token token2)
{
	char	*token1_value;
	char	*token2_value;

	if (token1.type != token2.type)
	{
		//ft_printf("TYPE DIFFERENCE WITH %s AND %s\n",
		//	DEBUG_token_type_stringify(token1.type),
		//	DEBUG_token_type_stringify(token2.type));
		return (false);
	}
	if (token1.offset != token2.offset)
	{
		//ft_printf("OFFSET DIFFERENCE WITH %d AND %d\n",
		//	(int)token1.offset,
		//	(int)token2.offset);
		return (false);
	}
	if (token1.value.len != token2.value.len)
	{
		//ft_printf("VALUE LENGTH DIFFERENCE WITH %d AND %d\n",
		//	(int)token1.value.len,
		//	(int)token2.value.len);
		return (false);
	}
	if (token1.value.data == NULL && token2.value.data != NULL)
	{
		//ft_printf("VALUE DIFFERENCE WITH NULL AND %s\n",
		//	buff_get_string(&token2.value));
		return (false);
	}
	else if (token1.value.data != NULL && token2.value.data == NULL)
	{
		//ft_printf("VALUE DIFFERENCE WITH %s AND NULL\n",
		//	buff_get_string(&token1.value));
		return (false);
	}
	else if (token1.value.data == NULL && token2.value.data == NULL)
		return (/*ft_printf("\n"), */true);
	else
	{
		token1_value = buff_get_string(&token1.value);
		token2_value = buff_get_string(&token2.value);
		if (strcmp(token1_value, token2_value) != 0)
		{
			//ft_printf("VALUE DIFFERENCE WITH '%s' AND '%s'\n",
			//	token1_value,
			//	token2_value);
			return (false);
		}
	}
	return (/*ft_printf("\n"), */true);
}
