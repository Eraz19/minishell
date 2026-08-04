/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:48:35 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:57:44 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "scanner.h"
#include "expansion_.h"
#include "shell.h"
#include "lexer.h"
#include "token_recognition_context.h"

bool	flag_is_active(uint bitset, uint flag)
{
	return ((bitset & flag) != 0);
}

t_error	forward_word_item(t_word *word_exp, t_word *word)
{
	t_error		err;
	t_word_item	item;

	err = word_fpop(&item, word);
	if (err.type)
		return (err);
	err = word_push(word_exp, item);
	if (err.type)
		return (err);
	return (error(ERR_NO));
}

t_error	join_expansion(t_string *out, t_expansion *in, t_string *ifs)
{
	size_t		i;
	t_error		err;
	t_string	str;

	string_init(out, 0, NULL, 0);
	if (in->len == 0)
		return (error(ERR_NO));
	i = 0;
	while (in->len > 0)
	{
		err = expansion_fpop(&str, in);
		if (err.type)
			return (string_free(out), err);
		if (i != 0 && !string_append_n(out, ifs->data, 1))
			err = error_sys();
		if (!err.type && !string_append(out, &str))
			err = error_sys();
		if (err.type)
			return (string_free(&str), string_free(out), err);
		++i;
	}
	return (string_free(&str), err);
}

t_error	prepare_str_for_expansion(
			t_context_stack *context_out,
			t_ast_vector *ast_vec_out,
			t_string *src)
{
	t_error						err;
	t_token						token;
	t_scanner					*scanner;
	t_token_recognition_context	scan_args;

	err = shell_get_new_scanner(&scanner, SCAN_MODE_STRING, src->data);
	if (err.type)
		return (err);
	scan_args = none_context_rules(&scanner->lexer);
	if (scanner_scan_word(scanner, &token, scan_args).type)
	{
		token_free(&token);
		return (err = scanner->err, shell_destroy_last_instance(), err);
	}
	string_free(src);
	vector_take(context_out, &token.contexts);
	vector_take(ast_vec_out, &token.ast_vector);
	string_take_string(src, &token.value);
	return (token_free(&token), shell_destroy_last_instance());
}

t_error	get_ifs(t_string *ifs)
{
	t_error	err;

	string_init(ifs, 0, NULL, 0);
	err = env_get_from_const("IFS", ifs);
	if (err.type != ERR_NO && err.type != ERR_VAR_NOT_FOUND)
		return (string_free(ifs), err);
	if (err.type == ERR_VAR_NOT_FOUND)
	{
		err = error(ERR_NO);
		if (!string_append_n(ifs, " \t\n", 3))
		{
			err = error_sys();
			return (string_free(ifs), err);
		}
	}
	else if (ifs->data == NULL)
	{
		if (!string_append_n(ifs, "", -1))
		{
			err = error_sys();
			return (string_free(ifs), err);
		}
	}
	return (err);
}
