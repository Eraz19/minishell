#include "body_.h"
#include "scanner.h"

t_error	get_body_line(t_body *body, char *EOL, size_t *i)
{
	char	*start;
	size_t	line_len;

	start = body->item->input.data + *i;
	if (EOL == NULL)
		line_len = str_len(start);
	else
		line_len = (size_t)(EOL - start) + 1;
	*i += line_len;
	if (!string_init(&body->line, 0, start, (long)line_len))
		return (body->err = error_sys());
	return (body->err);
}

bool	is_line_delimiter(t_body *body)
{
	if (body->item->mode == HEREDOC_MODE_TAB_STRIP)
		string_trim_leading(&body->line, '\t');
	return (string_cmp(&body->line, &body->item->delim));
}

t_error	body_continuation(t_body *body, bool *continuation)
{
	if (body->item->is_tty)
	{
		if (*continuation == false)
			*body->item->i = body->i;
		*continuation = true;
		return (scanner_read_continuation(&body->item->input), body->err);
	}
	else
	{
		body->item->delim.data[body->item->delim.len - 1] = '\0';
		body->err = error_print(error(ERR_REDIRECTION), "heredoc",
			"missing delimiter", NULL, "'%s'", body->item->delim.data);
		return (body->err);
	}
}

t_error	get_body_content(t_body *body)
{
	char	*match_EOL;
	bool	continuation;

	continuation = false;
	while (true)
	{
		if (body->item->input.data[body->i] == '\0')
		{
			if (body_continuation(body, &continuation).type)
				return (body->err);
		}
		match_EOL = str_chr(body->item->input.data + body->i, '\n');
		if (get_body_line(body, match_EOL, &body->i).type)
			return (body->err);
		if (is_line_delimiter(body))
		{
			if (!continuation)
				*body->item->i = body->i;
			return (body->err);
		}
		if (!string_append(&body->content, &body->line))
			return (body->err = error_sys());
		string_free(&body->line);
	}
}
