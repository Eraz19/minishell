/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 10:13:09 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/15 12:52:15 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "_lexer.h"
#include "./token/_token.h"

#define  TEST_COUNT 160

typedef enum e_test_type
{
	TEST_WITH_CONTINUATION,
	TEST_WITHOUT_CONTINUATION,
}	t_test_type;

typedef struct s_test_result_without_continuation
{
	t_token *failing_token;
	bool	is_token_success;
	size_t	success_token_count;
}	t_test_result_without_continuation;
typedef struct s_test_without_continuation
{
	const char							*input;
	t_test_result_without_continuation	result;
	size_t								token_count;
	t_token								result_token[7];
}	t_test_without_continuation;


typedef struct s_test_result_with_continuation
{
	t_test_result_without_continuation	base;
	t_lexer								failing_lexer;
	bool								is_lexer_success;
	size_t								success_lexer_count;
}	t_test_result_with_continuation;
typedef struct s_test_with_continuation_chunk
{
	const char			*input;
	size_t				token_count;
	t_token				result_token[7];
	t_lexer_snapshot	lexer_snapshot;
}	t_test_with_continuation_chunk;
typedef struct s_test_with_continuation
{
	t_test_result_with_continuation	result;
	t_test_with_continuation_chunk	continuation[7];
	size_t							continuation_count;
}	t_test_with_continuation;

typedef union u_test
{
	t_test_with_continuation	with;
	t_test_without_continuation	without;
}	t_test;

typedef struct s_lexer_test
{
	const char	*id;
	const char	*name;
	t_test_type	type;
	t_test		test;
}	t_lexer_test;



t_buff	buff_init_unsafe(const char *str)
{
	t_buff res;

	buff_init(&res, 0, str, (long)str_len(str));
	return (res);
}

void	test_without_continuation(t_lexer *lexer, t_lexer_test *test)
{
	size_t						i;
	t_token						*res;
	t_test_without_continuation	*test_;

	i = 0;
	res = NULL;
	test_ = &test->test.without;
	lexer->input = str_dup(test_->input);
	while (i < test_->token_count)
	{
		lex_line(&res, lexer);
		if (res == NULL)
		{
			test_->result.is_token_success = false;
			return (free_lexer(lexer));
		}
		if (DEBUG_is_token_equal(*res, test_->result_token[i]))
		{
			ft_printf("%s ", DEBUG_token_type_stringify(res->type));
			++test_->result.success_token_count;
			free_token(&res);
		}
		else
		{
			test_->result.failing_token = res;
			test_->result.is_token_success = false;
			return (free_lexer(lexer));
		}
		++i;
	}
}

void	test_with_continuation(t_lexer *lexer, t_lexer_test *test)
{
	size_t						i;
	size_t						j;
	t_token						*res;
	t_test_with_continuation	*test_;
	size_t						total_token_count;
	char						*old_input;

	test_ = &test->test.with;
	if (test_->continuation_count == 0)
		return ;
	i = 0;
	res = NULL;
	lexer->input = str_dup(test_->continuation[0].input);
	while (i < test_->continuation_count)
	{
		if (i > 0)
		{
			old_input = lexer->input;
			lexer->input = str_join(old_input, test_->continuation[i].input);
			free(old_input);
		}
		lex_line(&res, lexer);
		DEBUG_print_lexer_state(lexer);
		if (test_->continuation[i].token_count > 0)
		{
			if (res == NULL)
			{
				test_->result.base.is_token_success = false;
				break ;
			}
			if (!DEBUG_lexer_equal(lexer, &test_->continuation[i].lexer_snapshot))
			{
				test_->result.failing_lexer = *lexer;
				test_->result.is_lexer_success = false;
				break ;
			}
			++test_->result.success_lexer_count;
			j = 0;
			while (res != NULL)
			{
				if (j >= test_->continuation[i].token_count)
				{
					test_->result.base.failing_token = res;
					test_->result.base.is_token_success = false;
					break ;
				}
				if (DEBUG_is_token_equal(*res, test_->continuation[i].result_token[j]))
					++test_->result.base.success_token_count;
				else
				{
					test_->result.base.failing_token = res;
					test_->result.base.is_token_success = false;
					break ;
				}
				free_token(&res);
				++j;
				lex_line(&res, lexer);
			}
			if (!test_->result.base.is_token_success)
				break ;
			if (j != test_->continuation[i].token_count)
			{
				test_->result.base.is_token_success = false;
				break ;
			}
		}
		else
		{
			if (res != NULL)
			{
				test_->result.base.failing_token = res;
				test_->result.base.is_token_success = false;
				break ;
			}
			if (DEBUG_lexer_equal(lexer, &test_->continuation[i].lexer_snapshot))
				++test_->result.success_lexer_count;
			else
			{
				test_->result.failing_lexer = *lexer;
				test_->result.is_lexer_success = false;
				break ;
			}
		}
		++i;
	}
	free_lexer(lexer);
	total_token_count = 0;
	i = 0;
	while (i < test_->continuation_count)
		total_token_count += test_->continuation[i++].token_count;
	if (test_->result.base.is_token_success
		&& test_->result.base.success_token_count != total_token_count)
		test_->result.base.is_token_success = false;
}

void	test_lexer(t_lexer_test *tests)
{
	size_t	i;
	t_lexer	lexer =
	{
		.i = 0,
		.ctx.len = 0,
		.ctx.size = 0,
		.ctx.data = NULL,
		.input = NULL,
		.script_path = NULL,
		.is_completed = true,
		.continuation_i = -1,
		.total_removed_count = 0,
		.current_removed_count = 0,
	};

	i = 0;
	while (i < TEST_COUNT)
	{
		ft_printf("========================================\n");
		ft_printf("Test %s: '%s'\n", tests[i].id, tests[i].name);
		ft_printf("++++++++++++++++++++++++++++++++++++++++\n");
		if (tests[i].type == TEST_WITH_CONTINUATION)
			test_with_continuation(&lexer, &tests[i]);
		else
			test_without_continuation(&lexer, &tests[i]);
		ft_printf("\n++++++++++++++++++++++++++++++++++++++++\n");
		if (tests[i].type == TEST_WITH_CONTINUATION)
		{
			if (!tests[i].test.with.result.is_lexer_success)
			{
				ft_printf("FAILED to exit lexer with correct state\n");
				ft_printf("========================================\n");
				break;
			}
			if (!tests[i].test.with.result.base.is_token_success)
			{
				ft_printf("FAILED to tokenize at %d\n",
					(int)tests[i].test.with.result.base.success_token_count);
				DEBUG_print_token(tests[i].test.with.result.base.failing_token);
				ft_printf("========================================\n");
				break;
			}
		}
		else
		{
			if (!tests[i].test.without.result.is_token_success)
			{
				ft_printf("FAILED to tokenize at %d\n",
					(int)tests[i].test.without.result.success_token_count);
				DEBUG_print_token(tests[i].test.without.result.failing_token);
				ft_printf("========================================\n");
				break;
			}
		}
		ft_printf("SUCCESS\n");
		ft_printf("========================================\n");
		++i;
	}
}

int	main(void)
{
	t_lexer_test	tests[TEST_COUNT] =
	{
		// 1. Trivial inputs
		{
			.id = "1",
			.name = "",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "",
				.token_count = 1,
				.result_token =
				{
					(t_token){.type = EOF, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				},
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL
				}				
			}
		},
		{
			.id = "2",
			.name = "   ",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "   ",
				.token_count = 1,
				.result_token =
				{
					(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				},
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				}				
			}
		},
		{
			.id = "3",
			.name = "\t\t",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "\t\t",
				.token_count = 1,
				.result_token =
				{
					(t_token){.type = EOF, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				},
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				}				
			}
		},
		{
			.id = "4",
			.name = "\n",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "\n",
				.token_count = 2,
				.result_token =
				{
					(t_token){.type = NEWLINE, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = EOF, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				},
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
			}
		},
		{
			.id = "5",
			.name = "\n\n\n",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "\n\n\n",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = NEWLINE, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = NEWLINE, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = NEWLINE, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				},
			}
		},
		{
			.id = "6",
			.name = " \n ",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = " \n ",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = NEWLINE, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				},
			}
		},
		// 2. Simple words
		{
			.id = "7",
			.name = "echo hello",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "echo hello",
				.token_count = 3,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("echo")},
					(t_token){.type = TOKEN, .offset = 5, .value = buff_init_unsafe("hello")},
					(t_token){.type = EOF, .offset = 10, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				},
			}
		},
		{
			.id = "8",
			.name = "  echo   hello  ",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "  echo   hello  ",
				.token_count = 3,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 2, .value = buff_init_unsafe("echo")},
					(t_token){.type = TOKEN, .offset = 9, .value = buff_init_unsafe("hello")},
					(t_token){.type = EOF, .offset = 16, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "9",
			.name = "\t\techo\t\thello",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "\t\techo\t\thello",
				.token_count = 3,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 2, .value = buff_init_unsafe("echo")},
					(t_token){.type = TOKEN, .offset = 8, .value = buff_init_unsafe("hello")},
					(t_token){.type = EOF, .offset = 13, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "10",
			.name = "abc",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "abc",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("abc")},
					(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "11",
			.name = "echo a b c d e",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "echo a b c d e",
				.token_count = 7,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("echo")},
					(t_token){.type = TOKEN, .offset = 5, .value = buff_init_unsafe("a")},
					(t_token){.type = TOKEN, .offset = 7, .value = buff_init_unsafe("b")},
					(t_token){.type = TOKEN, .offset = 9, .value = buff_init_unsafe("c")},
					(t_token){.type = TOKEN, .offset = 11, .value = buff_init_unsafe("d")},
					(t_token){.type = TOKEN, .offset = 13, .value = buff_init_unsafe("e")},
					(t_token){.type = EOF, .offset = 14, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "12",
			.name = "echo\n",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "echo\n",
				.token_count = 3,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("echo")},
					(t_token){.type = NEWLINE, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = EOF, .offset = 5, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "13",
			.name = "a\nb",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a\nb",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a")},
					(t_token){.type = NEWLINE, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 2, .value = buff_init_unsafe("b")},
					(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "14",
			.name = "a;b",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a;b",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a")},
					(t_token){.type = SCOLON, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 2, .value = buff_init_unsafe("b")},
					(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		// 3. Operators (single-char and maximal munch)
		{
			.id = "15",
			.name = "a|b",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a|b",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a")},
					(t_token){.type = PIPE, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 2, .value = buff_init_unsafe("b")},
					(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "16",
			.name = "a||b",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a||b",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a")},
					(t_token){.type = OR_IF, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 3, .value = buff_init_unsafe("b")},
					(t_token){.type = EOF, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "17",
			.name = "a&b",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a&b",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a")},
					(t_token){.type = AMPERSAND, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 2, .value = buff_init_unsafe("b")},
					(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "18",
			.name = "a&&b",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a&&b",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a")},
					(t_token){.type = AND_IF, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 3, .value = buff_init_unsafe("b")},
					(t_token){.type = EOF, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "19",
			.name = ";",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = ";",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = SCOLON, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = EOF, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "20",
			.name = ";;",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = ";;",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = DSEMI, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = EOF, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "21",
			.name = ";;;",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = ";;;",
				.token_count = 3,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = DSEMI, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = SCOLON, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "22",
			.name = "|||",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "|||",
				.token_count = 3,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = OR_IF, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = PIPE, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "23",
			.name = "&&&",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "&&&",
				.token_count = 3,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = AND_IF, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = AMPERSAND, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "24",
			.name = ">>>",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = ">>>",
				.token_count = 3,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = DGREAT, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = GREAT, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "25",
			.name = "<<<",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "<<<",
				.token_count = 3,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = DLESS, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = LESS, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "26",
			.name = "(a)",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "(a)",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = LPARENTHESIS, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 1, .value = buff_init_unsafe("a")},
					(t_token){.type = RPARENTHESIS, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "27",
			.name = "( a )",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "( a )",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = LPARENTHESIS, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 2, .value = buff_init_unsafe("a")},
					(t_token){.type = RPARENTHESIS, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = EOF, .offset = 5, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "28",
			.name = "((a))",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "((a))",
				.token_count = 6,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = LPARENTHESIS, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = LPARENTHESIS, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 2, .value = buff_init_unsafe("a")},
					(t_token){.type = RPARENTHESIS, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = RPARENTHESIS, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = EOF, .offset = 5, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		// 4. Operators terminate words without spaces
		{
			.id = "29",
			.name = "cat<file",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "cat<file",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("cat")},
					(t_token){.type = LESS, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 4, .value = buff_init_unsafe("file")},
					(t_token){.type = EOF, .offset = 8, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "30",
			.name = "a|b|c",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a|b|c",
				.token_count = 6,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a")},
					(t_token){.type = PIPE, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 2, .value = buff_init_unsafe("b")},
					(t_token){.type = PIPE, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 4, .value = buff_init_unsafe("c")},
					(t_token){.type = EOF, .offset = 5, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "31",
			.name = "a&&b||c",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a&&b||c",
				.token_count = 6,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a")},
					(t_token){.type = AND_IF, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 3, .value = buff_init_unsafe("b")},
					(t_token){.type = OR_IF, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 6, .value = buff_init_unsafe("c")},
					(t_token){.type = EOF, .offset = 7, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "32",
			.name = "echo>out",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "echo>out",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("echo")},
					(t_token){.type = GREAT, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 5, .value = buff_init_unsafe("out")},
					(t_token){.type = EOF, .offset = 8, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "33",
			.name = "(ls)",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "(ls)",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = LPARENTHESIS, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 1, .value = buff_init_unsafe("ls")},
					(t_token){.type = RPARENTHESIS, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = EOF, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		// 5. Redirections
		{
			.id = "34",
			.name = "a > b",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a > b",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a")},
					(t_token){.type = GREAT, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 4, .value = buff_init_unsafe("b")},
					(t_token){.type = EOF, .offset = 5, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "35",
			.name = "a >> b",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a >> b",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a")},
					(t_token){.type = DGREAT, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 5, .value = buff_init_unsafe("b")},
					(t_token){.type = EOF, .offset = 6, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "36",
			.name = "a < b",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a < b",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a")},
					(t_token){.type = LESS, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 4, .value = buff_init_unsafe("b")},
					(t_token){.type = EOF, .offset = 5, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "37",
			.name = "a <> b",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a <> b",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a")},
					(t_token){.type = LESSGREAT, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 5, .value = buff_init_unsafe("b")},
					(t_token){.type = EOF, .offset = 6, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "38",
			.name = "a >| b",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a >| b",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a")},
					(t_token){.type = CLOBBER, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 5, .value = buff_init_unsafe("b")},
					(t_token){.type = EOF, .offset = 6, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "39",
			.name = "a >& 2",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a >& 2",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a")},
					(t_token){.type = GREATAND, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 5, .value = buff_init_unsafe("2")},
					(t_token){.type = EOF, .offset = 6, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "40",
			.name = "a <& 2",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a <& 2",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a")},
					(t_token){.type = LESSAND, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 5, .value = buff_init_unsafe("2")},
					(t_token){.type = EOF, .offset = 6, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "41",
			.name = "2>file",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "2>file",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = IO_NUMBER, .offset = 0, .value = buff_init_unsafe("2")},
					(t_token){.type = GREAT, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 2, .value = buff_init_unsafe("file")},
					(t_token){.type = EOF, .offset = 6, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "42",
			.name = "2 >file",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "2 >file",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("2")},
					(t_token){.type = GREAT, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 3, .value = buff_init_unsafe("file")},
					(t_token){.type = EOF, .offset = 7, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "43",
			.name = "a2>file",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a2>file",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a2")},
					(t_token){.type = GREAT, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 3, .value = buff_init_unsafe("file")},
					(t_token){.type = EOF, .offset = 7, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "44",
			.name = "10>file",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "10>file",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = IO_NUMBER, .offset = 0, .value = buff_init_unsafe("10")},
					(t_token){.type = GREAT, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 3, .value = buff_init_unsafe("file")},
					(t_token){.type = EOF, .offset = 7, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		// 6. Single-quote context
		{
			.id = "45",
			.name = "'hello'",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "'hello'",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("'hello'")},
					(t_token){.type = EOF, .offset = 7, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "46",
			.name = "'hello world'",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "'hello world'",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("'hello world'")},
					(t_token){.type = EOF, .offset = 13, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "47",
			.name = "''",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "''",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("''")},
					(t_token){.type = EOF, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "48",
			.name = "'a''b'",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "'a''b'",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("'a''b'")},
					(t_token){.type = EOF, .offset = 6, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "49",
			.name = "'a'b'c'",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "'a'b'c'",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("'a'b'c'")},
					(t_token){.type = EOF, .offset = 7, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "50",
			.name = "'a' 'b'",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "'a' 'b'",
				.token_count = 3,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("'a'")},
					(t_token){.type = TOKEN, .offset = 4, .value = buff_init_unsafe("'b'")},
					(t_token){.type = EOF, .offset = 7, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "51",
			.name = "'a\\nb'",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "'a\\nb'",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("'a\\nb'")},
					(t_token){.type = EOF, .offset = 6, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "52",
			.name = "'a\\\nb'",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "'a\\\nb'",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("'a\\\nb'")},
					(t_token){.type = EOF, .offset = 6, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "53",
			.name = "'$HOME'",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "'$HOME'",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("'$HOME'")},
					(t_token){.type = EOF, .offset = 7, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "54",
			.name = "'a\"b'",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "'a\"b'",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("'a\"b'")},
					(t_token){.type = EOF, .offset = 5, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		// 7. Double-quote context
		{
			.id = "55",
			.name = "\"hello\"",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "\"hello\"",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("\"hello\"")},
					(t_token){.type = EOF, .offset = 7, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "56",
			.name = "\"hello world\"",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "\"hello world\"",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("\"hello world\"")},
					(t_token){.type = EOF, .offset = 13, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "57",
			.name = "\"\"",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "\"\"",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("\"\"")},
					(t_token){.type = EOF, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "58",
			.name = "\"a\"\"b\"",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "\"a\"\"b\"",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("\"a\"\"b\"")},
					(t_token){.type = EOF, .offset = 6, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "59",
			.name = "\"a\"b\"c\"",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "\"a\"b\"c\"",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("\"a\"b\"c\"")},
					(t_token){.type = EOF, .offset = 7, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "60",
			.name = "\"a $b c\"",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "\"a $b c\"",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("\"a $b c\"")},
					(t_token){.type = EOF, .offset = 8, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "61",
			.name = "\"\\$\"",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "\"\\$\"",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("\"\\$\"")},
					(t_token){.type = EOF, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "62",
			.name = "\"\\\"\"",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "\"\\\"\"",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("\"\\\"\"")},
					(t_token){.type = EOF, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "63",
			.name = "\"\\\\\"",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "\"\\\\\"",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("\"\\\\\"")},
					(t_token){.type = EOF, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "64",
			.name = "\"\\a\"",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "\"\\a\"",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("\"\\a\"")},
					(t_token){.type = EOF, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "65",
			.name = "\"a\\\nb\"",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "\"a\\\nb\"",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("\"ab\"")},
					(t_token){.type = EOF, .offset = 6, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "66",
			.name = "\"a 'b' c\"",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "\"a 'b' c\"",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("\"a 'b' c\"")},
					(t_token){.type = EOF, .offset = 9, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		// 8. Mixed quoting / words abutting
		{
			.id = "67",
			.name = "a\"b\"c",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a\"b\"c",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a\"b\"c")},
					(t_token){.type = EOF, .offset = 5, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "68",
			.name = "\"a\"'b'c",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "\"a\"'b'c",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("\"a\"'b'c")},
					(t_token){.type = EOF, .offset = 7, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "69",
			.name = "\"a b\" c",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "\"a b\" c",
				.token_count = 3,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("\"a b\"")},
					(t_token){.type = TOKEN, .offset = 6, .value = buff_init_unsafe("c")},
					(t_token){.type = EOF, .offset = 7, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "70",
			.name = "'a b'\"c d\"",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "'a b'\"c d\"",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("'a b'\"c d\"")},
					(t_token){.type = EOF, .offset = 10, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "71",
			.name = "a' 'b",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a' 'b",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a' 'b")},
					(t_token){.type = EOF, .offset = 5, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		// 9. Backslash escapes (NONE context)
		{
			.id = "72",
			.name = "a\\ b",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a\\ b",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a\\ b")},
					(t_token){.type = EOF, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "73",
			.name = "a\\\\b",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a\\\\b",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a\\\\b")},
					(t_token){.type = EOF, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "74",
			.name = "\\|",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "\\|",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("\\|")},
					(t_token){.type = EOF, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "75",
			.name = "\\;",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "\\;",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("\\;")},
					(t_token){.type = EOF, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "76",
			.name = "\\$HOME",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "\\$HOME",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("\\$HOME")},
					(t_token){.type = EOF, .offset = 6, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "77",
			.name = "a\\\nb",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a\\\nb",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("ab")},
					(t_token){.type = EOF, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "78",
			.name = "echo a\\\nb",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "echo a\\\nb",
				.token_count = 3,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("echo")},
					(t_token){.type = TOKEN, .offset = 5, .value = buff_init_unsafe("ab")},
					(t_token){.type = EOF, .offset = 9, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "79",
			.name = "a\\\n\\\nb",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a\\\n\\\nb",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("ab")},
					(t_token){.type = EOF, .offset = 6, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "80",
			.name = "\\a",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "\\a",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("\\a")},
					(t_token){.type = EOF, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		// 10. Command substitution
		/*
		{
			.id = "81",
			.name =
			.type = TEST_WITHOUT_CONTINUATION,	
			.input = "$(echo hi)",
			.token_count = 2,
			.result =
			{
				.is_token_success = true,
				.success_token_count = 0,
				.failing_token = NULL,
			},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("$(echo hi)")},
					(t_token){.type = EOF, .offset = 10, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "82",
			.name =
			.type = TEST_WITHOUT_CONTINUATION,	
			.input = "a$(b)c",
			.token_count = 2,
			.result =
			{
				.is_token_success = true,
				.success_token_count = 0,
				.failing_token = NULL,
			},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a$(b)c")},
					(t_token){.type = EOF, .offset = 6, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "83",
			.name =
			.type = TEST_WITHOUT_CONTINUATION,	
			.input = "$(echo \"a b\")",
			.token_count = 2,
			.result =
			{
				.is_token_success = true,
				.success_token_count = 0,
				.failing_token = NULL,
			},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("$(echo \"a b\")")},
					(t_token){.type = EOF, .offset = 14, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "84",
			.name =
			.type = TEST_WITHOUT_CONTINUATION,	
			.input = "$(echo $(date))",
			.token_count = 2,
			.result =
			{
				.is_token_success = true,
				.success_token_count = 0,
				.failing_token = NULL,
			},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("$(echo $(date))")},
					(t_token){.type = EOF, .offset = 15, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "85",
			.name =
			.type = TEST_WITHOUT_CONTINUATION,	
			.input = "$(case x in *) echo;; esac)",
			.token_count = 2,
			.result =
			{
				.is_token_success = true,
				.success_token_count = 0,
				.failing_token = NULL,
			},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("$(case x in *) echo;; esac)")},
					(t_token){.type = EOF, .offset = 27, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "86",
			.name =
			.type = TEST_WITHOUT_CONTINUATION,	
			.input = "\"$(echo hi)\"",
			.token_count = 2,
			.result =
			{
				.is_token_success = true,
				.success_token_count = 0,
				.failing_token = NULL,
			},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("\"$(echo hi)\"")},
					(t_token){.type = EOF, .offset = 12, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "87",
			.name =
			.type = TEST_WITHOUT_CONTINUATION,	
			.input = "'$(echo hi)'",
			.token_count = 2,
			.result =
			{
				.is_token_success = true,
				.success_token_count = 0,
				.failing_token = NULL,
			},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("'$(echo hi)'")},
					(t_token){.type = EOF, .offset = 12, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "88",
			.name =
			.type = TEST_WITHOUT_CONTINUATION,	
			.input = "$()",
			.token_count = 2,
			.result =
			{
				.is_token_success = true,
				.success_token_count = 0,
				.failing_token = NULL,
			},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("$()")},
					(t_token){.type = EOF, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "89",
			.name =
			.type = TEST_WITHOUT_CONTINUATION,	
			.input = "$(\necho hi\n)",
			.token_count = 2,
			.result =
			{
				.is_token_success = true,
				.success_token_count = 0,
				.failing_token = NULL,
			},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("$(\necho hi\n)")},
					(t_token){.type = EOF, .offset = 13, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		*/
		// 11. Backticks
		{
			.id = "90",
			.name = "`echo hi`",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "`echo hi`",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("`echo hi`")},
					(t_token){.type = EOF, .offset = 9, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "91",
			.name = "`echo \\`echo hi\\``",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "`echo \\`echo hi\\``",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("`echo \\`echo hi\\``")},
					(t_token){.type = EOF, .offset = 18, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "92",
			.name = "`echo \\$x`",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "`echo \\$x`",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("`echo \\$x`")},
					(t_token){.type = EOF, .offset = 10, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "93",
			.name = "`echo a\\\nb`",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "`echo a\\\nb`",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("`echo a\\\nb`")},
					(t_token){.type = EOF, .offset = 11, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "94",
			.name = "a`b`c",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a`b`c",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a`b`c")},
					(t_token){.type = EOF, .offset = 5, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		// 12. Parameter expansion
		{
			.id = "95",
			.name = "$var",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "$var",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("$var")},
					(t_token){.type = EOF, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "96",
			.name = "${var}",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "${var}",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("${var}")},
					(t_token){.type = EOF, .offset = 6, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "97",
			.name = "${var:-default}",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "${var:-default}",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("${var:-default}")},
					(t_token){.type = EOF, .offset = 15, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "98",
			.name = "${var:-a b}",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "${var:-a b}",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("${var:-a b}")},
					(t_token){.type = EOF, .offset = 11, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "99",
			.name = "${var:-\"a b\"}",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "${var:-\"a b\"}",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("${var:-\"a b\"}")},
					(t_token){.type = EOF, .offset = 13, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "100",
			.name = "${var:-\\}}",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "${var:-\\}}",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("${var:-\\}}")},
					(t_token){.type = EOF, .offset = 10, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "101",
			.name = "${#var}",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "${#var}",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("${#var}")},
					(t_token){.type = EOF, .offset = 7, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "102",
			.name = "${var%%pattern}",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "${var%%pattern}",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("${var%%pattern}")},
					(t_token){.type = EOF, .offset = 15, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "103",
			.name = "a${b}c",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a${b}c",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a${b}c")},
					(t_token){.type = EOF, .offset = 6, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		// 13. Arithmetic expansion
		{
			.id = "104",
			.name = "$((1+2))",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "$((1+2))",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("$((1+2))")},
					(t_token){.type = EOF, .offset = 8, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "105",
			.name = "$(( 1 + 2 ))",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "$(( 1 + 2 ))",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("$(( 1 + 2 ))")},
					(t_token){.type = EOF, .offset = 12, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "106",
			.name = "$(($a+$b))",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "$(($a+$b))",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("$(($a+$b))")},
					(t_token){.type = EOF, .offset = 10, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "107",
			.name = "$(((1+2)*3))",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "$(((1+2)*3))",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("$(((1+2)*3))")},
					(t_token){.type = EOF, .offset = 12, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "108",
			.name = "a$((1))b",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a$((1))b",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a$((1))b")},
					(t_token){.type = EOF, .offset = 8, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		// 13b. Arithmetic expansion — parenthesis nesting
		{
			.id = "108b",
			.name = "$((1+(2*3)))",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "$((1+(2*3)))",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("$((1+(2*3)))")},
					(t_token){.type = EOF, .offset = 12, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "108c",
			.name = "$((1+(2+(3))))",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "$((1+(2+(3))))",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("$((1+(2+(3))))")},
					(t_token){.type = EOF, .offset = 14, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "108d",
			.name = "$(((1+2)*3))",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "$(((1+2)*3))",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("$(((1+2)*3))")},
					(t_token){.type = EOF, .offset = 12, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		// 14. Comments
		{
			.id = "109",
			.name = "# just a comment",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "# just a comment",
				.token_count = 1,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = EOF, .offset = 16, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "110",
			.name = "echo a # comment",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "echo a # comment",
				.token_count = 3,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("echo")},
					(t_token){.type = TOKEN, .offset = 5, .value = buff_init_unsafe("a")},
					(t_token){.type = EOF, .offset = 16, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "111",
			.name = "echo a # comment\necho b",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "echo a # comment\necho b",
				.token_count = 6,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("echo")},
					(t_token){.type = TOKEN, .offset = 5, .value = buff_init_unsafe("a")},
					(t_token){.type = NEWLINE, .offset = 16, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 17, .value = buff_init_unsafe("echo")},
					(t_token){.type = TOKEN, .offset = 22, .value = buff_init_unsafe("b")},
					(t_token){.type = EOF, .offset = 23, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "112",
			.name = "echo a#notacomment",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "echo a#notacomment",
				.token_count = 3,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("echo")},
					(t_token){.type = TOKEN, .offset = 5, .value = buff_init_unsafe("a#notacomment")},
					(t_token){.type = EOF, .offset = 18, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "113",
			.name = "echo \"a # not comment\"",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "echo \"a # not comment\"",
				.token_count = 3,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("echo")},
					(t_token){.type = TOKEN, .offset = 5, .value = buff_init_unsafe("\"a # not comment\"")},
					(t_token){.type = EOF, .offset = 22, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "114",
			.name = "echo '# not comment'",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "echo '# not comment'",
				.token_count = 3,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("echo")},
					(t_token){.type = TOKEN, .offset = 5, .value = buff_init_unsafe("'# not comment'")},
					(t_token){.type = EOF, .offset = 20, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "115",
			.name = "#comment",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "#comment",
				.token_count = 1,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = EOF, .offset = 8, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		// 15. Multi-line and newline behavior
		{
			.id = "116",
			.name = "echo a \\\nb",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "echo a \\\nb",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("echo")},
					(t_token){.type = TOKEN, .offset = 5, .value = buff_init_unsafe("a")},
					(t_token){.type = TOKEN, .offset = 9, .value = buff_init_unsafe("b")},
					(t_token){.type = EOF, .offset = 10, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "117",
			.name = "\"a\nb\"",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "\"a\nb\"",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("\"a\nb\"")},
					(t_token){.type = EOF, .offset = 5, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "118",
			.name = "'a\nb'",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "'a\nb'",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("'a\nb'")},
					(t_token){.type = EOF, .offset = 5, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		/*{
			.id = "119",
			.name =
			.type = TEST_WITHOUT_CONTINUATION,	
			.input = "$(echo\nhi)",
			.token_count = 2,
			.result =
			{
				.is_token_success = true,
				.success_token_count = 0,
				.failing_token = NULL,
			},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("$(echo\nhi)")},
					(t_token){.type = EOF, .offset = 11, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},*/
		// 16. Heredoc operator-line tokenization
		{
			.id = "120",
			.name = "cat <<EOF",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "cat <<EOF",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("cat")},
					(t_token){.type = DLESS, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 6, .value = buff_init_unsafe("EOF")},
					(t_token){.type = EOF, .offset = 9, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "121",
			.name = "cat <<-EOF",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "cat <<-EOF",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("cat")},
					(t_token){.type = DLESSDASH, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 7, .value = buff_init_unsafe("EOF")},
					(t_token){.type = EOF, .offset = 10, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "122",
			.name = "cat <<'EOF'",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "cat <<'EOF'",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("cat")},
					(t_token){.type = DLESS, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 6, .value = buff_init_unsafe("'EOF'")},
					(t_token){.type = EOF, .offset = 11, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "123",
			.name = "cat <<\\EOF",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "cat <<\\EOF",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("cat")},
					(t_token){.type = DLESS, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 6, .value = buff_init_unsafe("\\EOF")},
					(t_token){.type = EOF, .offset = 10, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "124",
			.name = "cat <<EOF arg",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "cat <<EOF arg",
				.token_count = 5,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("cat")},
					(t_token){.type = DLESS, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 6, .value = buff_init_unsafe("EOF")},
					(t_token){.type = TOKEN, .offset = 10, .value = buff_init_unsafe("arg")},
					(t_token){.type = EOF, .offset = 13, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		// 17. Pipelines, lists, groups
		{
			.id = "125",
			.name = "ls | grep foo",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "ls | grep foo",
				.token_count = 5,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("ls")},
					(t_token){.type = PIPE, .offset = 3, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 5, .value = buff_init_unsafe("grep")},
					(t_token){.type = TOKEN, .offset = 10, .value = buff_init_unsafe("foo")},
					(t_token){.type = EOF, .offset = 13, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "126",
			.name = "a && b || c",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a && b || c",
				.token_count = 6,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a")},
					(t_token){.type = AND_IF, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 5, .value = buff_init_unsafe("b")},
					(t_token){.type = OR_IF, .offset = 7, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 10, .value = buff_init_unsafe("c")},
					(t_token){.type = EOF, .offset = 11, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "127",
			.name = "a; b; c",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a; b; c",
				.token_count = 6,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a")},
					(t_token){.type = SCOLON, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 3, .value = buff_init_unsafe("b")},
					(t_token){.type = SCOLON, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 6, .value = buff_init_unsafe("c")},
					(t_token){.type = EOF, .offset = 7, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "128",
			.name = "(a; b)",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "(a; b)",
				.token_count = 6,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = LPARENTHESIS, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 1, .value = buff_init_unsafe("a")},
					(t_token){.type = SCOLON, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 4, .value = buff_init_unsafe("b")},
					(t_token){.type = RPARENTHESIS, .offset = 5, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = EOF, .offset = 6, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "129",
			.name = "a & b &",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "a & b &",
				.token_count = 5,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a")},
					(t_token){.type = AMPERSAND, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 4, .value = buff_init_unsafe("b")},
					(t_token){.type = AMPERSAND, .offset = 6, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = EOF, .offset = 7, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "130",
			.name = "cmd > out 2>&1",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "cmd > out 2>&1",
				.token_count = 7,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("cmd")},
					(t_token){.type = GREAT, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 6, .value = buff_init_unsafe("out")},
					(t_token){.type = IO_NUMBER, .offset = 10, .value = buff_init_unsafe("2")},
					(t_token){.type = GREATAND, .offset = 11, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = TOKEN, .offset = 13, .value = buff_init_unsafe("1")},
					(t_token){.type = EOF, .offset = 14, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		// 18. Unterminated / incomplete inputs
		{
			.id = "131",
			.name = "'hello",
			.type = TEST_WITH_CONTINUATION,
			.test.with =
			{
				.result =
				{
					.failing_lexer = {0}, 
					.is_lexer_success = true,
					.success_lexer_count = 0,
					.base =
					{
						.is_token_success = true,
						.success_token_count = 0,
						.failing_token = NULL,
					},
				},
				.continuation_count = 1,
				.continuation =
				{
					{
						.input = "'hello",
						.token_count = 0,
						.result_token = {},
						.lexer_snapshot =
						{
							.i                     = 0,
							.is_completed 	       = false,
							.continuation_i        = 6,
							.ctx.len               = 1,
							.ctx.data[0] 	       = {.type = SQUOTE, .nesting_depth = 0},
							.input				   = "'hello",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					}	
				}
			}
		},
		{
			.id = "132",
			.name = "\"hello",
			.type = TEST_WITH_CONTINUATION,
			.test.with =
			{
				.result =
				{
					.failing_lexer = {0}, 
					.is_lexer_success = true,
					.success_lexer_count = 0,
					.base =
					{
						.is_token_success = true,
						.success_token_count = 0,
						.failing_token = NULL,
					},
				},
				.continuation_count = 1,
				.continuation =
				{
					{
						.input = "\"hello",
						.token_count = 0,
						.result_token = {},
						.lexer_snapshot =
						{
							.i                     = 0,
							.ctx.len               = 1,
							.is_completed 	       = false,
							.continuation_i        = 6,
							.ctx.data[0]           = {.type = DQUOTE, .nesting_depth = 0},
							.input                 = "\"hello",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					}	
				}
			}
		},
		{
			.id = "133",
			.name = "`hello",
			.type = TEST_WITH_CONTINUATION,
			.test.with =
			{
				.result =
				{
					.failing_lexer = {0}, 
					.is_lexer_success = true,
					.success_lexer_count = 0,
					.base =
					{
						.is_token_success = true,
						.success_token_count = 0,
						.failing_token = NULL,
					},
				},
				.continuation_count = 1,
				.continuation =
				{
					{
						.input = "`hello",
						.token_count = 0,
						.result_token = {},
						.lexer_snapshot =
						{
							.i                     = 0,
							.ctx.len               = 1,
							.is_completed 	       = false,
							.continuation_i        = 6,
							.ctx.data[0]           = {.type = BACKTICK, .nesting_depth = 0},
							.input                 = "`hello",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					}	
				}
			}
		},
		/*{
			.id = "134",
			.type = TEST_WITH_CONTINUATION,
			.test.with =
			{
						.result =
						.failing_lexer = {0}, 
						.is_lexer_success = true,
						.success_lexer_count = 0,
				{	.base =
					{
					.is_token_success = true,
						.success_token_count = 0,
						.failing_token = NULL,
					},
				},
				.token_count = 0,
				.continuation_count = 0,
				.result_token = {},.continuation
				 =
				{
				}
				
			.input = "$(echo",
			.continuation =
			{
				{
					.input = NULL,
					.lexer_snapshot =
					{
						.i                     = 6,
						.ctx.len               = 1,
						.ctx.data[0]           = {.type = CMD_SUB, .nesting_depth = 0},
						.input                 = "$(echo",
						.total_removed_count   = 0,
						.current_removed_count = 0,
					}
				}
			},
		},*/
		{
			.id = "135",
			.name = "${var",
			.type = TEST_WITH_CONTINUATION,
			.test.with =
			{
				.result =
				{
					.failing_lexer = {0}, 
					.is_lexer_success = true,
					.success_lexer_count = 0,
					.base =
					{
						.is_token_success = true,
						.success_token_count = 0,
						.failing_token = NULL,
					},
				},
				.continuation_count = 1,
				.continuation =
				{
					{
						.input = "${var",
						.token_count = 0,
						.result_token = {},
						.lexer_snapshot =
						{
							.i                     = 0,
							.ctx.len               = 1,
							.is_completed 	       = false,
							.continuation_i        = 5,
							.ctx.data[0]           = {.type = PARAM, .nesting_depth = 0},
							.input                 = "${var",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					}	
				}
			}
		},
		{
			.id = "136",
			.name = "$((1+2)",
			.type = TEST_WITH_CONTINUATION,
			.test.with =
			{
				.result =
				{
					.failing_lexer = {0}, 
					.is_lexer_success = true,
					.success_lexer_count = 0,
					.base =
					{
						.is_token_success = true,
						.success_token_count = 0,
						.failing_token = NULL,
					},
				},
				.continuation_count = 1,
				.continuation =
				{
					{
						.input = "$((1+2)",
						.token_count = 0,
						.result_token = {},				
						.lexer_snapshot =
						{
							.i                     = 0,
							.ctx.len               = 1,
							.is_completed 	       = false,
							.continuation_i        = 6,
							.ctx.data[0]           = {.type = ARITH, .nesting_depth = 0},
							.input                 = "$((1+2)",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					}	
				}
			}
		},
		{
			.id = "137",
			.name = "\\",		
			.type = TEST_WITH_CONTINUATION,
			.test.with =
			{
				.result =
				{
					.failing_lexer = {0}, 
					.is_lexer_success = true,
					.success_lexer_count = 0,
					.base =
					{
						.is_token_success = true,
						.success_token_count = 0,
						.failing_token = NULL,
					},
				},
				.continuation_count = 1,
				.continuation =
				{
					{
						.input = "\\",
						.token_count = 0,
						.result_token = {},
						.lexer_snapshot =
						{
							.i                     = 0,
							.ctx.len               = 0,
							.is_completed 	       = false,
							.continuation_i        = 0,
							.ctx.data[0]           = {.type = NONE, .nesting_depth = 0},
							.input                 = "\\",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					}	
				}
			}
		},
		/*{
			.id = "138",
			.type = TEST_WITH_CONTINUATION,
			.test.with =
			{
						.result =
						.failing_lexer = {0}, 
						.is_lexer_success = true,
						.success_lexer_count = 0,
				{	.base =
					{
					.is_token_success = true,
						.success_token_count = 0,
						.failing_token = NULL,
					},
				},
				.token_count = 0,
				.continuation_count = 0,
				.result_token = {},.continuation
				 =
				{
				}
				
			.input = "$(case x in *) echo;;",
			.continuation =
			{
				{
					.input = NULL,
					.lexer_snapshot =
					{
						.i                     = 21,
						.ctx.len               = 1,
						.ctx.data[0]           = {.type = CMD_SUB, .nesting_depth = 0},
						.input                 = "$(case x in *) echo;;",
						.total_removed_count   = 0,
						.current_removed_count = 0,
					}
				}
			},
		},*/
		{
			.id = "146",
			.name = "'ab'",
			.type = TEST_WITH_CONTINUATION,
			.test.with =
			{
				.result =
				{
					.failing_lexer = {0}, 
					.is_lexer_success = true,
					.success_lexer_count = 0,
					.base =
					{
						.is_token_success = true,
						.success_token_count = 0,
						.failing_token = NULL,
					},
				},
				.continuation_count = 2,
				.continuation =
				{
					{
						.input = "'a",
						.token_count = 0,
						.result_token = {},
						.lexer_snapshot =
						{
							.i                     = 0,
							.ctx.len               = 1,
							.is_completed 	       = false,
							.continuation_i        = 2,
							.ctx.data[0]           = {.type = SQUOTE, .nesting_depth = 0},
							.input                 = "'a",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					},
					{
						.input = "b'",
						.token_count = 2,
						.result_token =
						{
							(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("'ab'")},
							(t_token){.type = EOF, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
						},
						.lexer_snapshot =
						{
							.i                     = 4,
							.ctx.len               = 0,
							.is_completed 	       = true,
							.continuation_i        = -1,
							.ctx.data[0]           = {.type = NONE, .nesting_depth = 0},
							.input                 = "'ab'",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					}	
				}
			}
		},
		{
			.id = "147",
			.name = "\"a$b\"",
			.type = TEST_WITH_CONTINUATION,
			.test.with =
			{
				.result =
				{
					.failing_lexer = {0}, 
					.is_lexer_success = true,
					.success_lexer_count = 0,
					.base =
					{
						.is_token_success = true,
						.success_token_count = 0,
						.failing_token = NULL,
					},
				},
				.continuation_count = 2,
				.continuation =
				{
					{
						.input = "\"a",
						.token_count = 0,
						.result_token = {},
						.lexer_snapshot =
						{
							.i                     = 0,
							.ctx.len               = 1,
							.is_completed 	       = false,
							.continuation_i        = 2,
							.ctx.data[0]           = {.type = DQUOTE, .nesting_depth = 0},
							.input                 = "\"a",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					},
					{
						.input = "$b\"",
						.token_count = 2,
						.result_token =
						{
							(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("\"a$b\"")},
							(t_token){.type = EOF, .offset = 5, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
						},
						.lexer_snapshot =
						{
							.i                     = 5,
							.ctx.len               = 0,
							.is_completed 	       = true,
							.continuation_i        = -1,
							.ctx.data[0]           = {.type = NONE, .nesting_depth = 0},
							.input                 = "\"a$b\"",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					}	
				}
			}
		},
		{
			.id = "148",
			.name = "`echo hi`",
			.type = TEST_WITH_CONTINUATION,
			.test.with =
			{
				.result =
				{
					.failing_lexer = {0}, 
					.is_lexer_success = true,
					.success_lexer_count = 0,
					.base =
					{
						.is_token_success = true,
						.success_token_count = 0,
						.failing_token = NULL,
					},
				},
				.continuation_count = 2,
				.continuation =
				{
					{
						.input = "`echo ",
						.token_count = 0,
						.result_token = {},
						.lexer_snapshot =
						{
							.i                     = 0,
							.ctx.len               = 1,
							.is_completed 	       = false,
							.continuation_i        = 6,
							.ctx.data[0]           = {.type = BACKTICK, .nesting_depth = 0},
							.input                 = "`echo ",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					},
					{
						.input = "hi`",
						.token_count = 2,
						.result_token =
						{
							(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("`echo hi`")},
							(t_token){.type = EOF, .offset = 9, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
						},
						.lexer_snapshot =
						{
							.i                     = 9,
							.ctx.len               = 0,
							.is_completed 	       = true,
							.continuation_i        = -1,
							.ctx.data[0]           = {.type = NONE, .nesting_depth = 0},
							.input                 = "`echo hi`",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					}	
				}
			}
		},
		/*{
			.id = "131",
			.type = TEST_WITH_CONTINUATION,
			.test.with =
			{
				.result =
				{
					.failing_lexer = {0}, 
					.is_lexer_success = true,
					.success_lexer_count = 0,
					.base =
					{
						.is_token_success = true,
						.success_token_count = 0,
						.failing_token = NULL,
					},
				},
				.token_count = 2,
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("$(echo hi)")},
					(t_token){.type = EOF, .offset = 9, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				},
				.continuation_count = 1,
				.continuation =
				{
					{
						.input = "$(echo",
						.emit_token	= false,
						.lexer_snapshot =
						{
							.i                     = 5,
							.ctx.len               = 1,
							.ctx.data[0]           = {.type = CMD_SUB, .nesting_depth = 0},
							.input                 = "$(echo",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					},
					{
						.input = " hi)",
						.emit_token = true,
						.lexer_snapshot =
						{
							.i                     = 9,
							.ctx.len               = 0,
							.ctx.data[0]           = {.type = NONE, .nesting_depth = 0},
							.input                 = "$(echo hi)",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					}	
				}
			}
		},*/
		{
			.id = "149",
			.name = "${var:-def}",
			.type = TEST_WITH_CONTINUATION,
			.test.with =
			{
				.result =
				{
					.failing_lexer = {0}, 
					.is_lexer_success = true,
					.success_lexer_count = 0,
					.base =
					{
						.is_token_success = true,
						.success_token_count = 0,
						.failing_token = NULL,
					},
				},

				.continuation_count = 2,
				.continuation =
				{
					{
						.input = "${var",
						.token_count = 0,
						.result_token = {},
						.lexer_snapshot =
						{
							.i                     = 0,
							.ctx.len               = 1,
							.is_completed 	       = false,
							.continuation_i        = 5,
							.ctx.data[0]           = {.type = PARAM, .nesting_depth = 0},
							.input                 = "${var",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					},
					{
						.input = ":-def}",
						.token_count = 2,
						.result_token =
						{
							(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("${var:-def}")},
							(t_token){.type = EOF, .offset = 11, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
						},
						.lexer_snapshot =
						{
							.i                     = 11,
							.ctx.len               = 0,
							.is_completed 	       = true,
							.continuation_i        = -1,
							.ctx.data[0]           = {.type = NONE, .nesting_depth = 0},
							.input                 = "${var:-def}",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					}	
				}
			}
		},
		{
			.id = "150",
			.name = "$((1+2))",
			.type = TEST_WITH_CONTINUATION,
			.test.with =
			{
				.result =
				{
					.failing_lexer = {0}, 
					.is_lexer_success = true,
					.success_lexer_count = 0,
					.base =
					{
						.is_token_success = true,
						.success_token_count = 0,
						.failing_token = NULL,
					},
				},
				.continuation_count = 2,
				.continuation =
				{
					{
						.input = "$((1+2",
						.token_count = 0,
						.result_token = {},
						.lexer_snapshot =
						{
							.i                     = 0,
							.ctx.len               = 1,
							.is_completed 	       = false,
							.continuation_i        = 6,
							.ctx.data[0]           = {.type = ARITH, .nesting_depth = 0},
							.input                 = "$((1+2",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					},
					{
						.input = "))",
						.token_count = 2,
						.result_token =
						{
							(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("$((1+2))")},
							(t_token){.type = EOF, .offset = 8, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
						},
						.lexer_snapshot =
						{
							.i                     = 8,
							.ctx.len               = 0,
							.is_completed 	       = true,
							.continuation_i        = -1,
							.ctx.data[0]           = {.type = NONE, .nesting_depth = 0},
							.input                 = "$((1+2))",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					}	
				}
			}
		},
		{
			.id = "151",
			.name = "$((1+2))",
			.type = TEST_WITH_CONTINUATION,
			.test.with =
			{
				.result =
				{
					.failing_lexer = {0}, 
					.is_lexer_success = true,
					.success_lexer_count = 0,
					.base =
					{
						.is_token_success = true,
						.success_token_count = 0,
						.failing_token = NULL,
					},
				},
				.continuation_count = 2,
				.continuation =
				{
					{
						.input = "$((1+2)",
						.token_count = 0,
						.result_token = {},
						.lexer_snapshot =
						{
							.i                     = 0,
							.ctx.len               = 1,
							.is_completed 	       = false,
							.continuation_i        = 6,
							.ctx.data[0]           = {.type = ARITH, .nesting_depth = 0},
							.input                 = "$((1+2)",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					},
					{
						.input = ")",
						.token_count = 2,
						.result_token =
						{
							(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("$((1+2))")},
							(t_token){.type = EOF, .offset = 8, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
						},
						.lexer_snapshot =
						{
							.i                     = 8,
							.ctx.len               = 0,
							.is_completed 	       = true,
							.continuation_i        = -1,
							.ctx.data[0]           = {.type = NONE, .nesting_depth = 0},
							.input                 = "$((1+2))",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					}	
				}
			}
		},
		{
			.id = "152",
			.name = "'ab'",
			.type = TEST_WITH_CONTINUATION,
			.test.with =
			{
				.result =
				{
					.failing_lexer = {0},
					.is_lexer_success = true,
					.success_lexer_count = 0,
					.base =
					{
						.is_token_success = true,
						.success_token_count = 0,
						.failing_token = NULL,
					},
				},
				.continuation_count = 2,
				.continuation =
				{
					{
						.input = "'ab",
						.token_count = 0,
						.result_token = {},
						.lexer_snapshot =
						{
							.i                     = 0,
							.ctx.len               = 1,
							.is_completed          = false,
							.continuation_i        = 3,
							.ctx.data[0]           = {.type = SQUOTE, .nesting_depth = 0},
							.input                 = "'ab",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					},
					{
						.input = "'",
						.token_count = 2,
						.result_token =
						{
							(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("'ab'")},
							(t_token){.type = EOF, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
						},
						.lexer_snapshot =
						{
							.i                     = 4,
							.ctx.len               = 0,
							.is_completed          = true,
							.continuation_i        = -1,
							.ctx.data[0]           = {.type = NONE, .nesting_depth = 0},
							.input                 = "'ab'",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					}
				}
			}
		},
		{
			.id = "153",
			.name = "\"ab\"",
			.type = TEST_WITH_CONTINUATION,
			.test.with =
			{
				.result =
				{
					.failing_lexer = {0},
					.is_lexer_success = true,
					.success_lexer_count = 0,
					.base =
					{
						.is_token_success = true,
						.success_token_count = 0,
						.failing_token = NULL,
					},
				},
				.continuation_count = 2,
				.continuation =
				{
					{
						.input = "\"ab",
						.token_count = 0,
						.result_token = {},
						.lexer_snapshot =
						{
							.i                     = 0,
							.ctx.len               = 1,
							.is_completed          = false,
							.continuation_i        = 3,
							.ctx.data[0]           = {.type = DQUOTE, .nesting_depth = 0},
							.input                 = "\"ab",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					},
					{
						.input = "\"",
						.token_count = 2,
						.result_token =
						{
							(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("\"ab\"")},
							(t_token){.type = EOF, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
						},
						.lexer_snapshot =
						{
							.i                     = 4,
							.ctx.len               = 0,
							.is_completed          = true,
							.continuation_i        = -1,
							.ctx.data[0]           = {.type = NONE, .nesting_depth = 0},
							.input                 = "\"ab\"",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					}
				}
			}
		},
		{
			.id = "154",
			.name = "`ab`",
			.type = TEST_WITH_CONTINUATION,
			.test.with =
			{
				.result =
				{
					.failing_lexer = {0},
					.is_lexer_success = true,
					.success_lexer_count = 0,
					.base =
					{
						.is_token_success = true,
						.success_token_count = 0,
						.failing_token = NULL,
					},
				},
				.continuation_count = 2,
				.continuation =
				{
					{
						.input = "`ab",
						.token_count = 0,
						.result_token = {},
						.lexer_snapshot =
						{
							.i                     = 0,
							.ctx.len               = 1,
							.is_completed          = false,
							.continuation_i        = 3,
							.ctx.data[0]           = {.type = BACKTICK, .nesting_depth = 0},
							.input                 = "`ab",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					},
					{
						.input = "`",
						.token_count = 2,
						.result_token =
						{
							(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("`ab`")},
							(t_token){.type = EOF, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
						},
						.lexer_snapshot =
						{
							.i                     = 4,
							.ctx.len               = 0,
							.is_completed          = true,
							.continuation_i        = -1,
							.ctx.data[0]           = {.type = NONE, .nesting_depth = 0},
							.input                 = "`ab`",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					}
				}
			}
		},
		{
			.id = "155",
			.name = "${ab}",
			.type = TEST_WITH_CONTINUATION,
			.test.with =
			{
				.result =
				{
					.failing_lexer = {0},
					.is_lexer_success = true,
					.success_lexer_count = 0,
					.base =
					{
						.is_token_success = true,
						.success_token_count = 0,
						.failing_token = NULL,
					},
				},
				.continuation_count = 2,
				.continuation =
				{
					{
						.input = "${ab",
						.token_count = 0,
						.result_token = {},
						.lexer_snapshot =
						{
							.i                     = 0,
							.ctx.len               = 1,
							.is_completed          = false,
							.continuation_i        = 4,
							.ctx.data[0]           = {.type = PARAM, .nesting_depth = 0},
							.input                 = "${ab",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					},
					{
						.input = "}",
						.token_count = 2,
						.result_token =
						{
							(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("${ab}")},
							(t_token){.type = EOF, .offset = 5, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
						},
						.lexer_snapshot =
						{
							.i                     = 5,
							.ctx.len               = 0,
							.is_completed          = true,
							.continuation_i        = -1,
							.ctx.data[0]           = {.type = NONE, .nesting_depth = 0},
							.input                 = "${ab}",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					}
				}
			}
		},
		{
			.id = "156",
			.name = "$((1+(2*3)))",
			.type = TEST_WITH_CONTINUATION,
			.test.with =
			{
				.result =
				{
					.failing_lexer = {0},
					.is_lexer_success = true,
					.success_lexer_count = 0,
					.base =
					{
						.is_token_success = true,
						.success_token_count = 0,
						.failing_token = NULL,
					},
				},

				.continuation_count = 2,
				.continuation =
				{
					{
						.input = "$((1+(2",
						.token_count = 0,
						.result_token = {},
						.lexer_snapshot =
						{
							.i                     = 0,
							.ctx.len               = 1,
							.is_completed          = false,
							.continuation_i        = 7,
							.ctx.data[0]           = {.type = ARITH, .nesting_depth = 1},
							.input                 = "$((1+(2",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					},
					{
						.input = "*3)))",
						.token_count = 2,
						.result_token =
						{
							(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("$((1+(2*3)))")},
							(t_token){.type = EOF, .offset = 12, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
						},
						.lexer_snapshot =
						{
							.i                     = 12,
							.ctx.len               = 0,
							.is_completed          = true,
							.continuation_i        = -1,
							.ctx.data[0]           = {.type = NONE, .nesting_depth = 0},
							.input                 = "$((1+(2*3)))",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					}
				}
			}
		},
		{
			.id = "157",
			.name = "$((1+(2*3)))",
			.type = TEST_WITH_CONTINUATION,
			.test.with =
			{
				.result =
				{
					.failing_lexer = {0},
					.is_lexer_success = true,
					.success_lexer_count = 0,
					.base =
					{
						.is_token_success = true,
						.success_token_count = 0,
						.failing_token = NULL,
					},
				},
				.continuation_count = 2,
				.continuation =
				{
					{
						.input = "$((1+(2*3)",
						.token_count = 0,
						.result_token = {},
						.lexer_snapshot =
						{
							.i                     = 0,
							.ctx.len               = 1,
							.is_completed          = false,
							.continuation_i        = 9,
							.ctx.data[0]           = {.type = ARITH, .nesting_depth = 1},
							.input                 = "$((1+(2*3)",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					},
					{
						.input = "))",
						.token_count = 2,
						.result_token =
						{
							(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("$((1+(2*3)))")},
							(t_token){.type = EOF, .offset = 12, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
						},
						.lexer_snapshot =
						{
							.i                     = 12,
							.ctx.len               = 0,
							.is_completed          = true,
							.continuation_i        = -1,
							.ctx.data[0]           = {.type = NONE, .nesting_depth = 0},
							.input                 = "$((1+(2*3)))",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					}
				}
			}
		},
		{
			.id = "158",
			.name = "'ab'",
			.type = TEST_WITH_CONTINUATION,
			.test.with =
			{
				.result =
				{
					.failing_lexer = {0}, 
					.is_lexer_success = true,
					.success_lexer_count = 0,
					.base =
					{
						.is_token_success = true,
						.success_token_count = 0,
						.failing_token = NULL,
					},
				},
				.continuation_count = 3,
				.continuation =
				{
					{
						.input = "'a",
						.token_count = 0,
						.result_token = {},
						.lexer_snapshot =
						{
							.i                     = 0,
							.ctx.len               = 1,
							.is_completed	       = false,
							.continuation_i        = 2,
							.ctx.data[0]           = {.type = SQUOTE, .nesting_depth = 0},
							.input                 = "'a",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					},
					{
						.input = "b",
						.token_count = 0,
						.result_token = {},
						.lexer_snapshot =
						{
							.i                     = 0,
							.ctx.len               = 1,
							.is_completed 	       = false,
							.continuation_i        = 3,
							.ctx.data[0]           = {.type = SQUOTE, .nesting_depth = 0},
							.input                 = "'ab",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					},
					{
						.input = "'",
						.token_count = 2,
						.result_token =
						{
							(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("'ab'")},
							(t_token){.type = EOF, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
						},
						.lexer_snapshot =
						{
							.i                     = 4,
							.ctx.len               = 0,
							.is_completed 	       = true,
							.continuation_i        = -1,
							.ctx.data[0]           = {.type = NONE, .nesting_depth = 0},
							.input                 = "'ab'",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					}	
				}
			}
		},
		{
			.id = "159",
			.name = "\"abc\"",
			.type = TEST_WITH_CONTINUATION,
			.test.with =
			{
				.result =
				{
					.failing_lexer = {0}, 
					.is_lexer_success = true,
					.success_lexer_count = 0,
					.base =
					{
						.is_token_success = true,
						.success_token_count = 0,
						.failing_token = NULL,
					},
				},
				.continuation_count = 3,
				.continuation =
				{
					{
						.input = "\"abc",
						.token_count = 0,
						.result_token = {},
						.lexer_snapshot =
						{
							.i                     = 0,
							.ctx.len               = 1,
							.is_completed	       = false,
							.continuation_i        = 4,
							.ctx.data[0]           = {.type = DQUOTE, .nesting_depth = 0},
							.input                 = "\"abc",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					},
					{
						.input = "",
						.token_count = 0,
						.result_token = {},
						.lexer_snapshot =
						{
							.i                     = 0,
							.ctx.len               = 1,
							.is_completed 	       = false,
							.continuation_i        = 4,
							.ctx.data[0]           = {.type = DQUOTE, .nesting_depth = 0},
							.input                 = "\"abc",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					},
					{
						.input = "\"",
						.token_count = 2,
						.result_token =
						{
							(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("\"abc\"")},
							(t_token){.type = EOF, .offset = 5, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
						},
						.lexer_snapshot =
						{
							.i                     = 5,
							.ctx.len               = 0,
							.is_completed 	       = true,
							.continuation_i        = -1,
							.ctx.data[0]           = {.type = NONE, .nesting_depth = 0},
							.input                 = "\"abc\"",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					}	
				}
			}
		},
		{
			.id = "160",
			.name = "${var:-\"abc",
			.type = TEST_WITH_CONTINUATION,
			.test.with =
			{
				.result =
				{
					.failing_lexer = {0}, 
					.is_lexer_success = true,
					.success_lexer_count = 0,
					.base =
					{
						.is_token_success = true,
						.success_token_count = 0,
						.failing_token = NULL,
					},
				},
				.continuation_count = 1,
				.continuation =
				{
					{
						.input = "${var:-\"abc",
						.token_count = 0,
						.result_token = {},
						.lexer_snapshot =
						{
							.i                     = 0,
							.ctx.len               = 2,
							.is_completed	       = false,
							.continuation_i        = 11,
							.ctx.data[0]           = {.type = PARAM, .nesting_depth = 0},
							.ctx.data[1]           = {.type = DQUOTE, .nesting_depth = 0},
							.input                 = "${var:-\"abc",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					}
				}
			}
		},
		{
			.id = "161",
			.name = "$(((1+2",
			.type = TEST_WITH_CONTINUATION,
			.test.with =
			{
				.result =
				{
					.failing_lexer = {0}, 
					.is_lexer_success = true,
					.success_lexer_count = 0,
					.base =
					{
						.is_token_success = true,
						.success_token_count = 0,
						.failing_token = NULL,
					},
				},
				.continuation_count = 1,
				.continuation =
				{
					{
						.input = "$(((1+2",
						.token_count = 0,
						.result_token = {},
						.lexer_snapshot =
						{
							.i                     = 0,
							.ctx.len               = 1,
							.is_completed	       = false,
							.continuation_i        = 7,
							.ctx.data[0]           = {.type = ARITH, .nesting_depth = 1},
							.input                 = "$(((1+2",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					}
				}
			}
		},
		{
			.id = "162",
			.name = "echo \\\nhi",
			.type = TEST_WITH_CONTINUATION,
			.test.with =
			{
				.result =
				{
					.failing_lexer = {0}, 
					.is_lexer_success = true,
					.success_lexer_count = 0,
					.base =
					{
						.is_token_success = true,
						.success_token_count = 0,
						.failing_token = NULL,
					},
				},
				.continuation_count = 3,
				.continuation =
				{
					{
						.input = "echo \\",
						.token_count = 1,
						.result_token =
						{
							(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("echo")},	
						},
						.lexer_snapshot =
						{
							.i                     = 4,
							.ctx.len               = 0,
							.is_completed	       = true,
							.continuation_i        = -1,
							.ctx.data[0]           = {.type = NONE, .nesting_depth = 0},
							.input                 = "echo \\",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					},
					{
						.input = "",
						.token_count = 0,
						.result_token = {},
						.lexer_snapshot =
						{
							.i                     = 5,
							.ctx.len               = 0,
							.is_completed	       = false,
							.continuation_i        = 5,
							.ctx.data[0]           = {.type = NONE, .nesting_depth = 0},
							.input                 = "echo \\",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					},
					{
						.input = "\nhi",
						.token_count = 2,
						.result_token =
						{
							(t_token){.type = TOKEN, .offset = 7, .value = buff_init_unsafe("hi")},
							(t_token){.type = EOF, .offset = 9, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
						},
						.lexer_snapshot =
						{
							.i                     = 7,
							.ctx.len               = 0,
							.is_completed	       = true,
							.continuation_i        = -1,
							.ctx.data[0]           = {.type = NONE, .nesting_depth = 0},
							.input                 = "echo hi",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					}
				}
			}
		},
		{
			.id = "163",
			.name = "echo \\\nhi\\more",
			.type = TEST_WITH_CONTINUATION,
			.test.with =
			{
				.result =
				{
					.failing_lexer = {0}, 
					.is_lexer_success = true,
					.success_lexer_count = 0,
					.base =
					{
						.is_token_success = true,
						.success_token_count = 0,
						.failing_token = NULL,
					},
				},
				.continuation_count = 3,
				.continuation =
				{
					{
						.input = "echo \\",
						.token_count = 1,
						.result_token =
						{
							(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("echo")},	
						},
						.lexer_snapshot =
						{
							.i                     = 4,
							.ctx.len               = 0,
							.is_completed	       = true,
							.continuation_i        = -1,
							.ctx.data[0]           = {.type = NONE, .nesting_depth = 0},
							.input                 = "echo \\",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					},
					{
						.input = "",
						.token_count = 0,
						.result_token = {},
						.lexer_snapshot =
						{
							.i                     = 5,
							.ctx.len               = 0,
							.is_completed	       = false,
							.continuation_i        = 5,
							.ctx.data[0]           = {.type = NONE, .nesting_depth = 0},
							.input                 = "echo \\",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					},
					{
						.input = "\nhi\\",
						.token_count = 0,
						.result_token = {},
						.lexer_snapshot =
						{
							.i                     = 5,
							.ctx.len               = 0,
							.is_completed	       = false,
							.continuation_i        = 7,
							.ctx.data[0]           = {.type = NONE, .nesting_depth = 0},
							.input                 = "echo hi\\",
							.total_removed_count   = 2,
							.current_removed_count = 0,
						}
					},
					{
						.input = "more",
						.token_count = 1,
						.result_token =
						{
							(t_token){.type = TOKEN, .offset = 7, .value = buff_init_unsafe("hi\\more")},
						},
						.lexer_snapshot =
						{
							.i                     = 13,
							.ctx.len               = 0,
							.is_completed	       = true,
							.continuation_i        = -1,
							.ctx.data[0]           = {.type = NONE, .nesting_depth = 0},
							.input                 = "echo hi\\more",
							.total_removed_count   = 0,
							.current_removed_count = 0,
						}
					}
				}
			}
		},
		// 19. Tricky composite cases
		/*{
			.id = "139",
			.type = TEST_WITHOUT_CONTINUATION,	
			.input = "echo \"$(echo \"nested\")\"",
			.token_count = 3,
			.result =
			{
				.is_token_success = true,
				.success_token_count = 0,
				.failing_token = NULL,
			},
			.result_token =
			{
				(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("echo")},
				(t_token){.type = TOKEN, .offset = 5, .value = buff_init_unsafe("\"$(echo \"nested\")\"")},
				(t_token){.type = EOF, .offset = 23, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			}
		},
		{
			.id = "140",
			.type = TEST_WITHOUT_CONTINUATION,	
			.input = "echo $(echo '$x')",
			.token_count = 3,
			.result =
			{
				.is_token_success = true,
				.success_token_count = 0,
				.failing_token = NULL,
			},
			.result_token =
			{
				(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("echo")},
				(t_token){.type = TOKEN, .offset = 5, .value = buff_init_unsafe("$(echo '$x')")},
				(t_token){.type = EOF, .offset = 17, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
			}
		},
		},*/
		{
			.id = "141",
			.name = "echo \"${var:-\"default\"}\"",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "echo \"${var:-\"default\"}\"",
				.token_count = 3,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("echo")},
					(t_token){.type = TOKEN, .offset = 5, .value = buff_init_unsafe("\"${var:-\"default\"}\"")},
					(t_token){.type = EOF, .offset = 24, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "142",
			.name = "echo \"$((1+2))\"",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "echo \"$((1+2))\"",
				.token_count = 3,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("echo")},
					(t_token){.type = TOKEN, .offset = 5, .value = buff_init_unsafe("\"$((1+2))\"")},
					(t_token){.type = EOF, .offset = 15, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		/*{
			.id = "143",
			.type = TEST_WITHOUT_CONTINUATION,	
			.input = "a\"b\"'c'\\$d$(e)${f}$((g))h",
			.token_count = 2,
			.result =
			{
				.is_token_success = true,
				.success_token_count = 0,
				.failing_token = NULL,
			},
				.result_token =
				{
					(t_token){.type = TOKEN, .offset = 0, .value = buff_init_unsafe("a\"b\"'c'\\$d$(e)${f}$((g))h")},
					(t_token){.type = EOF, .offset = 25, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},*/
		{
			.id = "144",
			.name = ">",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = ">",
				.token_count = 2,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = GREAT, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = EOF, .offset = 1, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		},
		{
			.id = "145",
			.name = "|||||",
			.type = TEST_WITHOUT_CONTINUATION,
			.test.without =
			{
				.input = "|||||",
				.token_count = 4,
				.result =
				{
					.is_token_success = true,
					.success_token_count = 0,
					.failing_token = NULL,
				},
				.result_token =
				{
					(t_token){.type = OR_IF, .offset = 0, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = OR_IF, .offset = 2, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = PIPE, .offset = 4, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
					(t_token){.type = EOF, .offset = 5, .value = (t_buff){.cap = 0, .len = 0, .data = NULL}},
				}
			},
		}
	};
	test_lexer(tests);
}
