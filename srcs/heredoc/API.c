#include "shell.h"
#include "body_.h"
#include "heredoc.h"
#include "heredoc_.h"
#include "scanner.h"
#include "expander.h"
#include "expansion_.h"

static t_error	heredoc_read_load_item(
				t_heredoc_item *item,
				const t_token *delim,
				t_heredoc *heredoc,
				t_scanner *scanner)
{
	t_lexer_input_stack_item	*input;

	*item = (t_heredoc_item){0};
	item->is_tty = heredoc->is_tty;
	item->mode = HEREDOC_MODE_NORMAL;
	if (expand_delim(heredoc, &item->delim, delim).type)
		return (heredoc->err);
	input = scanner->lexer.input;
	if (input != NULL)
		item->i = input->i;
	if (input == NULL && !string_init(&item->input, 1, "", -1))
		return (heredoc_item_free(item), heredoc->err = error_sys(),
			heredoc->err);
	if (input != NULL
		&& !string_init(&item->input, 0, input->str.data, (long)input->str.len))
		return (heredoc_item_free(item), heredoc->err = error_sys(),
			heredoc->err);
	return (heredoc->err);
}

static t_error	heredoc_read_body(t_string *out_body, t_heredoc_item *item,
		t_lexer_input_stack_item *input)
{
	t_body	body;

	body_init(&body);
	body_load(&body, item);
	if (get_body_content(&body).type)
		return (body_free(&body), body.err);
	string_free(out_body);
	if (!string_init(out_body, 0, body.content.data, (long)body.content.len))
		return (body_free(&body), error_sys());
	if (input != NULL)
		input->i = item->i;
	return (body_free(&body), error(ERR_NO));
}

t_error	heredoc_read(t_string *out_body, const t_token *delim)
{
	t_heredoc					*heredoc;
	t_scanner					*scanner;
	t_lexer_input_stack_item	*input;
	t_heredoc_item				item;

	heredoc = shell_get_heredoc();
	scanner = shell_get_scanner();
	if (heredoc == NULL || scanner == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	input = scanner->lexer.input;
	heredoc->err = heredoc_read_load_item(&item, delim, heredoc, scanner);
	if (heredoc->err.type)
		return (heredoc->err);
	heredoc->err = heredoc_read_body(out_body, &item, input);
	return (heredoc_item_free(&item), heredoc->err);
}
