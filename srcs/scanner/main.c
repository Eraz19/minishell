/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 10:13:09 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/14 20:52:06 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_scanner.h"
#include <stdlib.h>
#include <string.h>

void	print_token(t_token *token)
{
	ft_printf("- TOKEN ----------------------\n");
	if (token == NULL)
		ft_printf("NO TOKEN\n");
	else
	{
		ft_printf(
			"%s => '%s' at %d\n",
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

bool	is_token_equal(t_token token1, t_token token2)
{
	char	*token1_value;
	char	*token2_value;

	if (token1.type != token2.type)
		return (ft_printf("0"), false);
	if (token1.offset != token2.offset)
		return (ft_printf("1"), false);
	if (token1.value.len != token2.value.len)
	{
		//ft_printf("token1 %d | token2 %d", (int)token1.value.len, (int)token2.value.len);
		return (ft_printf("2"), false);
	}
	if (token1.value.data == NULL && token2.value.data != NULL)
		return (ft_printf("3"), false);
	else if (token1.value.data != NULL && token2.value.data == NULL)
		return (ft_printf("4"), false);
	else if (token1.value.data == NULL && token2.value.data == NULL)
		return (ft_printf("5"), true);
	else
	{
		token1_value = buff_get_string(&token1.value);
		token2_value = buff_get_string(&token2.value);
		if (strcmp(token1_value, token2_value) != 0)
			return (ft_printf("6"), false);
	}
	return (ft_printf("7"), true);
}

int	main(void)
{
	

	size_t	i;
	size_t	j;
	t_token	*res;
	t_lexer	lexer =
	{
		.i = 0,
		.ctx.len = 0,
		.ctx.size = 0,
		.ctx.data = NULL,
		.input = NULL,
		.script_path = NULL,	
	};
	const char	*tests[] =
	{
		"",
		"   ",
		"		",
		"\n",
		"\n\n\n",
		" \n ",

		"echo hello",
		"  echo   hello  ",
		"	echo	hello",
		"abc",
		"echo a b c d e",
		"echo\n",
		"a\nb",
		"a;b",
		
		"a|b",
		"a||b",
		"a&b",
		"a&&b",
		";",
		";;",
		";;;",
		"|||",
		"&&&",
		">>>",
		"<<<",
		"(a)",
		"( a )",
		"((a))",
		
		"cat<file",
		"a|b|c",
		"a&&b||c",
		"echo>out",
		"(ls)",
		
		"a > b",
		"a >> b",
		"a < b",
		"a <> b",
		"a >| b",
		"a >& 2",
		"a <& 2",
		"2>file",
		"2 >file",
		"a2>file",
		"10>file",

		"'hello'",
		"'hello world'",
		"''",
		"'a''b'",
		"'a'b'c'",
		"'a' 'b'",
		"'a\nb'",
		"a\\nb",
		"'$HOME'",
		"'a\"b'",
		NULL,
	};
	size_t	sizes[] = {
		1, 1, 1, 2, 4, 2,
		3, 3, 3, 2, 7, 3, 4, 4,
		4, 4, 4, 4, 2, 2, 3, 3, 3, 3, 3, 4, 4, 6,
		4, 6, 6, 4, 4,
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
		2, 2, 2, 2, 2, 3, 2, 2, 2, 2,
	};

	t_buff echo; buff_init(&echo, 0, NULL, -1); buff_append(&echo, "echo", 4);
	t_buff hello; buff_init(&hello, 0, NULL, -1); buff_append(&hello, "hello", 5);
	t_buff abc; buff_init(&abc, 0, NULL, -1); buff_append(&abc, "abc", 3);	
	t_buff a; buff_init(&a, 0, NULL, -1); buff_append(&a, "a", 1);
	t_buff b; buff_init(&b, 0, NULL, -1); buff_append(&b, "b", 1);
	t_buff c; buff_init(&c, 0, NULL, -1); buff_append(&c, "c", 1);
	t_buff d; buff_init(&d, 0, NULL, -1); buff_append(&d, "d", 1);
	t_buff e; buff_init(&e, 0, NULL, -1); buff_append(&e, "e", 1);
	t_buff cat; buff_init(&cat, 0, NULL, -1); buff_append(&cat, "cat", 3);
	t_buff file; buff_init(&file, 0, NULL, -1); buff_append(&file, "file", 4);
	t_buff out; buff_init(&out, 0, NULL, -1); buff_append(&out, "out", 3);
	t_buff ls; buff_init(&ls, 0, NULL, -1); buff_append(&ls, "ls", 2);
	t_buff _2; buff_init(&_2, 0, NULL, -1); buff_append(&_2, "2", 1);
	t_buff _10; buff_init(&_10, 0, NULL, -1); buff_append(&_10, "10", 2);
	t_buff a2; buff_init(&a2, 0, NULL, -1); buff_append(&a2, "a2", 2);
	
	t_buff hello_; buff_init(&hello_, 0, NULL, -1); buff_append(&hello_, "'hello'", 7);
	t_buff hello_world; buff_init(&hello_world, 0, NULL, -1); buff_append(&hello_world, "'hello world'", 13);
	t_buff empty; buff_init(&empty, 0, NULL, -1); buff_append(&empty, "''", 2);
	t_buff a_; buff_init(&a_, 0, NULL, -1); buff_append(&a_, "'a'", 3);
	t_buff b_; buff_init(&b_, 0, NULL, -1); buff_append(&b_, "'b'", 3);
	t_buff _a_b; buff_init(&_a_b, 0, NULL, -1); buff_append(&_a_b, "'a''b'", 6);
	t_buff _a_b_c; buff_init(&_a_b_c, 0, NULL, -1); buff_append(&_a_b_c, "'a'b'c'", 7);
	t_buff _a_n_b; buff_init(&_a_n_b, 0, NULL, -1); buff_append(&_a_n_b, "'a\\nb'", 6);
	t_buff _a_n_b_; buff_init(&_a_n_b_, 0, NULL, -1); buff_append(&_a_n_b_, "'a\\\nb'", 6);
	t_buff home; buff_init(&home, 0, NULL, -1); buff_append(&home, "'$HOME'", 7);
	t_buff a__b; buff_init(&a__b, 0, NULL, -1); buff_append(&a__b, "'a\"b'", 6);
	
	

	t_token	results[][7] =
	{
		{
			(t_token){.type = EOF, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = EOF, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = NEWLINE, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = EOF, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = NEWLINE, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = NEWLINE, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = NEWLINE, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = NEWLINE, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = echo},
			(t_token){.type = TOKEN, .offset = 5, .value = hello},
			(t_token){.type = EOF, .offset = 10, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 2, .value = echo},
			(t_token){.type = TOKEN, .offset = 9, .value = hello},
			(t_token){.type = EOF, .offset = 16, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 1, .value = echo},
			(t_token){.type = TOKEN, .offset = 6, .value = hello},
			(t_token){.type = EOF, .offset = 11, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = abc},
			(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = echo},
			(t_token){.type = TOKEN, .offset = 5, .value = a},
			(t_token){.type = TOKEN, .offset = 7, .value = b},
			(t_token){.type = TOKEN, .offset = 9, .value = c},
			(t_token){.type = TOKEN, .offset = 11, .value = d},
			(t_token){.type = TOKEN, .offset = 13, .value = e},
			(t_token){.type = EOF, .offset = 14, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = echo},
			(t_token){.type = NEWLINE, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = EOF, .offset = 5, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = a},
			(t_token){.type = NEWLINE, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = TOKEN, .offset = 2, .value = b},
			(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = a},
			(t_token){.type = SCOLON, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = TOKEN, .offset = 2, .value = b},
			(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = a},
			(t_token){.type = PIPE, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = TOKEN, .offset = 2, .value = b},
			(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = a},
			(t_token){.type = OR_IF, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = TOKEN, .offset = 3, .value = b},
			(t_token){.type = EOF, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = a},
			(t_token){.type = AMPERSAND, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = TOKEN, .offset = 2, .value = b},
			(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = a},
			(t_token){.type = AND_IF, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = TOKEN, .offset = 3, .value = b},
			(t_token){.type = EOF, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = SCOLON, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = EOF, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = DSEMI, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = EOF, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = DSEMI, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = SCOLON, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = OR_IF, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = PIPE, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = AND_IF, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = AMPERSAND, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = DGREAT, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = GREAT, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = DLESS, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = LESS, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = LPARENTHESIS, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = TOKEN, .offset = 1, .value = a},
			(t_token){.type = RPARENTHESIS, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = LPARENTHESIS, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = TOKEN, .offset = 2, .value = a},
			(t_token){.type = RPARENTHESIS, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = EOF, .offset = 5, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = LPARENTHESIS, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = LPARENTHESIS, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = TOKEN, .offset = 2, .value = a},
			(t_token){.type = RPARENTHESIS, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = RPARENTHESIS, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = EOF, .offset = 5, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = cat},
			(t_token){.type = LESS, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = TOKEN, .offset = 4, .value = file},
			(t_token){.type = EOF, .offset = 8, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = a},
			(t_token){.type = PIPE, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = TOKEN, .offset = 2, .value = b},
			(t_token){.type = PIPE, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = TOKEN, .offset = 4, .value = c},
			(t_token){.type = EOF, .offset = 5, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = a},
			(t_token){.type = AND_IF, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = TOKEN, .offset = 3, .value = b},
			(t_token){.type = OR_IF, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = TOKEN, .offset = 6, .value = c},
			(t_token){.type = EOF, .offset = 7, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = echo},
			(t_token){.type = GREAT, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = TOKEN, .offset = 5, .value = out},			
			(t_token){.type = EOF, .offset = 8, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = LPARENTHESIS, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = TOKEN, .offset = 1, .value = ls},
			(t_token){.type = RPARENTHESIS, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = EOF, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = a},
			(t_token){.type = GREAT, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = TOKEN, .offset = 4, .value = b},
			(t_token){.type = EOF, .offset = 5, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = a},
			(t_token){.type = DGREAT, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = TOKEN, .offset = 5, .value = b},
			(t_token){.type = EOF, .offset = 6, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = a},
			(t_token){.type = LESS, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = TOKEN, .offset = 4, .value = b},
			(t_token){.type = EOF, .offset = 5, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = a},
			(t_token){.type = LESSGREAT, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = TOKEN, .offset = 5, .value = b},
			(t_token){.type = EOF, .offset = 6, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = a},
			(t_token){.type = CLOBBER, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = TOKEN, .offset = 5, .value = b},
			(t_token){.type = EOF, .offset = 6, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = a},
			(t_token){.type = GREATAND, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = TOKEN, .offset = 5, .value = _2},
			(t_token){.type = EOF, .offset = 6, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = a},
			(t_token){.type = LESSAND, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = TOKEN, .offset = 5, .value = _2},
			(t_token){.type = EOF, .offset = 6, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = IO_NUMBER, .offset = 0, .value = _2},
			(t_token){.type = GREAT, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = TOKEN, .offset = 2, .value = file},
			(t_token){.type = EOF, .offset = 6, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = _2},
			(t_token){.type = GREAT, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = TOKEN, .offset = 3, .value = file},
			(t_token){.type = EOF, .offset = 7, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = a2},
			(t_token){.type = GREAT, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = TOKEN, .offset = 3, .value = file},
			(t_token){.type = EOF, .offset = 7, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = IO_NUMBER, .offset = 0, .value = _10},
			(t_token){.type = GREAT, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			(t_token){.type = TOKEN, .offset = 3, .value = file},
			(t_token){.type = EOF, .offset = 7, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},

		{
			(t_token){.type = TOKEN, .offset = 0, .value = hello_},
			(t_token){.type = EOF, .offset = 7, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = hello_world},
			(t_token){.type = EOF, .offset = 13, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = empty},
			(t_token){.type = EOF, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = _a_b},
			(t_token){.type = EOF, .offset = 6, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = _a_b_c},
			(t_token){.type = EOF, .offset = 7, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = a_},
			(t_token){.type = TOKEN, .offset = 4, .value = b_},
			(t_token){.type = EOF, .offset = 7, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = _a_n_b},
			(t_token){.type = EOF, .offset = 6, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = _a_n_b_},
			(t_token){.type = EOF, .offset = 6, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = home},
			(t_token){.type = EOF, .offset = 7, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		},
		{
			(t_token){.type = TOKEN, .offset = 0, .value = a__b},
			(t_token){.type = EOF, .offset = 5, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
		}
	};
	i = 0;
	while (tests[i] != NULL)
	{
		ft_printf("========================================\n");
		j = 0;
		res = NULL;
		lexer.i = 0;
		lexer.input = str_dup(tests[i]);
		while (j < sizes[i])
		{
			lex_line(&res, &lexer);
			print_token(res);
			if (is_token_equal(*res, results[i][j]))
				++j;
			else
				break;
		}
		if (j != sizes[i])
		{
			ft_printf("'%s' FAILED at token %d\n", tests[i], (int)j);
			print_token(res);
			free(lexer.input);
			lexer.input = NULL;
			lexer.i = 0;
			ft_printf("========================================\n");
			break;
		}
		else
			ft_printf("'%s' SUCCESS\n", tests[i]);
		//print_lexer_state(&lexer);
		ft_printf("========================================\n");
		++i;
	}
}
