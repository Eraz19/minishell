#include <unistd.h>
#include "alias.h"
#include "heredoc.h"
#include "reader_.h"
#include "scanner_.h"
#include "posix_helpers.h"

static t_error	scanner_stdin_input(t_string *res)
{
	t_error	err;

	err = posix_read_all(STDIN_FILENO, res);
	if (err.type == ERR_LIBC)
		return (reader_read_error(err, "stdin"));
	return (err);
}

static t_error	scanner_dup_command_input(
					t_scanner *scanner,
					t_lexer_input_stack_item *item)
{
	if (!string_init(&item->str, 0, scanner->source, -1))
		return (scanner->err = error_sys());
	if (!string_append_n(&item->str, "\n", 1))
	{
		scanner->err = error_sys();
		return (string_free(&item->str), scanner->err);
	}
	return (scanner->err);
}

t_error	scanner_read_input(t_scanner *scanner) 
{
	t_lexer_input_stack_item	*item;

	scanner->err = lexer_input_stack_item_init(&item);
	if (scanner->err.type)
		return (scanner->err);
	if (scanner->mode == INPUT_MODE_FILE)
		scanner->err = reader_file_input(&item->str, scanner->source);
	else if (scanner->mode == INPUT_MODE_STRING)
	{
		if (scanner_dup_command_input(scanner, item).type)
			return (lexer_input_stack_item_free(&item), scanner->err);
	}
	else if (scanner->mode == INPUT_MODE_STDIN_PIPE)
		scanner->err = scanner_stdin_input(&item->str);
	else if (scanner->mode == INPUT_MODE_STDIN_TTY)
		scanner->err = reader_new_input(&item->str); 
	if (scanner->err.type || item->str.len < 2)
		return (lexer_input_stack_item_free(&item), scanner->err);
	scanner->err = lexer_input_stack_push(&scanner->lexer.input_stack, item);
	return (scanner->err);
}

t_error	scanner_alias_expand(t_scanner *scanner, t_token *token)
{
	t_lexer_input_stack_item	*item;
	bool						expanded;

	scanner->err = lexer_input_stack_item_init(&item);
	if (scanner->err.type)
		return (scanner->err);
	scanner->err = alias_expand_token(&item->str, &expanded, &token->value);
	if (scanner->err.type || !expanded)
		return (lexer_input_stack_item_free(&item), scanner->err);
	scanner->err = lexer_input_stack_push(&scanner->lexer.input_stack, item);
	if (scanner->err.type)
	{
		(void)alias_on_expansion_end();
		return (lexer_input_stack_item_free(&item), scanner->err);
	}
	scanner->lexer.input = NULL;
	token_free(token);
	if (lexer_get_next_token(&scanner->lexer, token,
			scanner_lexer_rules(scanner)).type)
		return (scanner->err = scanner->lexer.err);
	if (token->type == TOKEN_TOKEN)
		return (scanner_alias_expand(scanner, token));
	return (scanner->err);
}

void	prepare_heredoc_read_args(
			t_scanner *scanner,
			t_heredoc_read_args *out,
			bool strip,
			const t_string *delim)
{
	if (scanner->lexer.input == NULL)
	{
		out->input = NULL;
		out->start = NULL;
	}
	else
	{
		out->input = &scanner->lexer.input->str;
		out->start = &scanner->lexer.input->i;
	}
	if (strip)
		out->mode = HEREDOC_MODE_TAB_STRIP;
	else
		out->mode = HEREDOC_MODE_NORMAL;
	out->is_tty = scanner->mode == INPUT_MODE_STDIN_TTY;
	out->delim = delim;
}
