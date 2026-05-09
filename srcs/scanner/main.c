/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 10:13:09 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/09 14:47:59 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_scanner.h"

void	print_token(t_token *token)
{
	ft_printf("- TOKEN ----------------------\n");
	if (token == NULL)
		ft_printf("NO TOKEN\n");
	else
	{
		ft_printf(
			"%s => %s at %d\n",
			DEBUG_token_type_stringify(token->type),
			buff_get_string(&token->value),
			(int)token->offset);
	}
	ft_printf("------------------------------\n");
}

void	print_lexer_state(t_lexer *lexer)
{
	ft_printf("\n- LEXER_STATE ----------------------\n");
	ft_printf("SCRIPT_PATH = %s\n", lexer->script_path);
	ft_printf("INPUT 	   = '%s'\n", lexer->input);
	ft_printf("INDEX 	   = %d\n", (int)lexer->i);
	ft_printf("\n------------------------------------\n");
}

int	main(void)
{
	t_lexer	lexer;
	t_token	*res;

	ft_printf("Prepare emvironment\n");
	res = NULL;
	lexer.i = 0;
	lexer.ctx.len = 0;
	lexer.ctx.size = 0;
	lexer.ctx.data = NULL;
	lexer.input = NULL;
	lexer.script_path = NULL;
	while (res == NULL || res->type != EOF)
	{
		res = get_next_token(&lexer);
		ft_printf("RES = %p\n", res);
		print_token(res);
		print_lexer_state(&lexer);
	}
}
