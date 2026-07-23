#include "params.h"
#include "scanner.h"
#include "expander_.h"
#include "expansion_.h"
#include "parser.h"
#include "shell.h"

bool    flag_is_active(uint bitset, uint flag)
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
	t_error		err;
	t_lexer		*lexer;
	t_string	lexer_src;

	err = shell_get_new_lexer(&lexer, SCAN_MODE_STRING);
	if (err.type)
		return (err);
	err = lexer_remove_escaped_newlines(lexer, src, str_context_rules());
	if (err.type)
		return (shell_destroy_last_instance(), err);
	parser_clear(lexer->scanner->parser);
	if (!string_dup(&lexer_src, src))
		return (err = error_sys(), shell_destroy_last_instance(), err);
	err = lexer_push_input(lexer, &lexer_src);
	if (err.type == ERR_NO)
		err = lexer_track_context(
				lexer,
				context_out,
				ast_vec_out,
				str_context_rules());
	return (shell_destroy_last_instance(), err);
}

t_error	get_ifs(t_string *ifs)
{
	t_error	err;

	string_init(ifs, 0, NULL, 0);
	err = params_get_from_const("IFS", ifs);
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
