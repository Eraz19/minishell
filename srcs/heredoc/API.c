#include <stdlib.h>
#include "shell.h"
#include "body_.h"
#include "heredoc.h"
#include "heredoc_.h"
#include "expander.h"
#include "heredoc_queue_.h"

t_error	heredoc_register(t_string *out, const t_token *delim, t_here_mode mode)
{
	t_heredoc_item	item;
	t_heredoc		*heredoc;

	heredoc = shell_get_heredoc();
	if (heredoc == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (create_heredoc_file(heredoc, out).type)
		return (heredoc->err);
	item.is_tty = heredoc->is_tty;
	if (!string_init(&item.path, 0, out->data, (long)out->len))
		return (heredoc->err = error_sys(), string_free(out), heredoc->err);
	if (expand_delim(heredoc, &item.delim, delim).type)
		return (string_free(out), heredoc_item_free(&item), heredoc->err);
	item.mode = mode;
	heredoc->err = heredoc_queue_push(&heredoc->queue, item);
	if (heredoc->err.type)
		return (string_free(out), heredoc_item_free(&item), heredoc->err);
	return (heredoc->err);
}

t_error	heredoc_read_body(
			t_heredoc *heredoc,
			const t_string *src,
			unsigned long *start)
{
	size_t			i;
	t_heredoc_item	item;
	t_body	body;

	i = 0;
	heredoc->err = heredoc_queue_pop(&heredoc->queue, &item);
	if (heredoc->err.type)
		return (heredoc->err);
	if (start == NULL || *start > item.input.len)
		heredoc->err = heredoc_item_load(&item, src, &i);
	else 
		heredoc->err = heredoc_item_load(&item, src, start);
	if (heredoc->err.type)
		return (heredoc_item_free(&item), heredoc->err);
	body_init(&body);
	body_load(&body, &item);
	heredoc->err = get_body_content(&body);
	if (heredoc->err.type)
	{
		heredoc_item_free(&item);
		return (body_free(&body), heredoc->err);
	}
	heredoc->err = save_body_in_file(&body.item->path, &body.content);
	return (heredoc_item_free(&item), body_free(&body), heredoc->err);
}

t_error	heredoc_read_body_from_input(const t_string *input, size_t *start)
{
	t_heredoc	*heredoc;

	heredoc = shell_get_heredoc();
	if (heredoc == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	while (heredoc->queue.len != 0)
	{
		if (heredoc_read_body(heredoc, input, start).type)
			return (heredoc->err);
	}
	return (heredoc->err);
}

t_error	heredoc_expand_body(const t_string *path)
{
	t_error		err;
	t_string	body;
	t_exp_flag	flags;
	t_expansion	expansion;

	flags = generate_heredoc_body_expand_flags();
	err = read_body_file(&body, path);
	if (err.type)
		return (err);
	err = expand_heredoc(&expansion, &body, flags);
	if (err.type)
		return (string_free(&body), err);
	string_free(&body);
	string_init(&body, 0, NULL, 0);
	if (expansion.len != 1)
		err = error(ERR_EXP_RESULT_INCOHERENT);
	else
		err = expansion_get(&body, &expansion, 0);
	if (err.type)
		return (string_free(&body), expansion_free(&expansion), err);
	err = save_body_in_file(path, &body);
	return (expansion_free(&expansion), string_free(&body), err);
}

t_error	heredoc_get_body_contexts(t_context_stack *out, const t_string *body)
{
	t_error					err;
	t_lexer					lexer;
	t_context_stack_item	*item;
	t_string				body_dup;

	if (!string_dup(&body_dup, body))
		return (error_sys());
	err = context_stack_item_init(&item, CONTEXT_HEREDOC);
	if (err.type)
		return (string_free(&body_dup), err);
	item->start = 0;
	item->end = body_dup.len;
	err = context_stack_push(out, item);
	if (err.type)
		return (free(item), string_free(&body_dup), err);
	lexer_init(&lexer);
	err = lexer_push_input(&lexer, &body_dup);
	if (!err.type)
		err = lexer_track_context(&lexer, out, body_context_rules());
	return (lexer_free(&lexer), err);
}
