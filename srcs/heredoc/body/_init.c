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

void	body_load(t_body *body, t_heredoc_item *item)
{
	body->i = *item->i;
	body->item = item;
}
