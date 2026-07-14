#include "body_.h"

void	body_init(t_body *body)
{
	*(body) = (t_body){0};
	context_stack_init(&body->contexts);
	string_init(&body->content, 0, NULL, 0);
}

void	body_free(t_body *body)
{
	string_free(&body->line);
	string_free(&body->input);
	string_free(&body->content);
	context_stack_free(&body->contexts);
	*(body) = (t_body){0};
}

t_error	body_load(t_body *body, t_heredoc_read_args *args)
{
	const t_string *input;

	input = args->input;
	if (input == NULL)
	{
		if (!string_init(&body->input, 1, "", -1))
			return (error_sys());
	}
	else
		if (!string_init(&body->input, 0, input->data, (long)input->len))
			return (error_sys());
	body->i = *(args->start);
	body->mode = args->mode;
	body->is_tty = args->is_tty;
	body->delim = *(args->delim);
	return (error(ERR_NO));
}
