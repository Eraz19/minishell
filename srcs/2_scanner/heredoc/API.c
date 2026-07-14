#include <stdlib.h>
#include "body_.h"
#include "heredoc.h"
#include "expander.h"

static t_error	heredoc_read_body(
					t_string *out,
					t_body *body,
					t_heredoc_read_args *args)
{
	t_error	err;

	err = body_load(body, args);
	if (err.type)
		return (err);
	err = get_body_content(body);
	if (err.type)
		return (err);
	if (!string_init(out, 0, body->content.data, (long)body->content.len))
		err = error_sys();
	return (err);
}

t_error	heredoc_read_body_from_input(t_string *out, t_heredoc_read_args *args)
{
	size_t	i;
	t_error	err;
	t_body	body;
	size_t	*start;

	i = 0;
	start = args->start;
	if (start != NULL && args->input != NULL && *start <= args->input->len)
		i = *start;
	args->start = &i;
	body_init(&body);
	err = heredoc_read_body(out, &body, args);
	if (!err.type && start != NULL && args->input != NULL)
	{
		*start = body.i;
		if (body.i > args->input->len)
			*start = args->input->len;
	}
	return (body_free(&body), err);
}

t_error	heredoc_expand_delim(t_string *out, const t_token *delim)
{
	t_error	err;
	int		exit_status;

	err = expand_token_merged(out, delim, &exit_status, EXP_QUOTE_REMOVAL);
	if (err.type)
		return (err);
	if (!string_append_n(out, "\n", 1))
		return (err = error_sys(), string_free(out), err);
	return (error(ERR_NO));
}

t_error	heredoc_prepare_for_expansion(t_context_stack *out, t_string *body)
{
	t_error					err;
	t_lexer					lexer;
	t_context_stack_item	*item;
	t_string				lexer_body;

	err = lexer_remove_escaped_newlines(body, body_context_rules());
	if (err.type)
		return (err);
	err = context_stack_item_init(&item, CONTEXT_HEREDOC);
	if (err.type)
		return (err);
	item->start = 0;
	item->end = body->len;
	err = context_stack_push(out, item);
	if (err.type)
		return (free(item), err);
	if (!string_dup(&lexer_body, body))
		return (error_sys());
	lexer_init(&lexer);
	err = lexer_push_input(&lexer, &lexer_body);
	if (!err.type)
		err = lexer_track_context(&lexer, out, body_context_rules());
	return (lexer_free(&lexer), err);
}
