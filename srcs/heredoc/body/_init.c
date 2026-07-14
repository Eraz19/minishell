#include "body_.h"

void	body_init(t_body *body)
{
	*(body) = (t_body){0};
	context_stack_init(&body->contexts);
	string_init(&body->content, 0, NULL, 0);
}

void	body_free(t_body *body)
{
	string_free(&body->content);
	string_free(&body->line);
	context_stack_free(&body->contexts);
	*(body) = (t_body){0};
}

t_error	body_load(t_body *body, t_heredoc_read_args *args)
{

	string_init(&body->input, 0, args->input->data, (long)args->input->len);
	body->input = args->input;
	body->i = *(args->start);
	body->delim = *(args->delim);
	body->is_tty = args->is_tty;
	body->mode = args->mode;
}
