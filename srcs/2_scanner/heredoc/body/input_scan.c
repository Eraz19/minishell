#include "body_.h"
#include "reader_.h"

t_error	get_body_line(t_body *body, char *EOL, size_t *i)
{
	char	*start;
	size_t	line_len;

	start = body->input.data + *i;
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
	if (body->mode == HEREDOC_MODE_TAB_STRIP)
		string_trim_leading(&body->line, '\t');
	return (string_cmp(&body->line, &body->delim));
}

static t_error	body_missing_delimiter(t_body *body)
{
	body->delim.data[body->delim.len - 1] = '\0';
	body->err = error_print(error(ERR_NO_DELIM), "heredoc",
		NULL, "'%s'", body->delim.data);
	return (body->err);
}

t_error	body_continuation(t_body *body, bool *continuation)
{
	if (body->is_tty)
	{
		*continuation = true;
		body->err = reader_continuation(&body->input);
		if (body->err.type == ERR_VEOF)
			return (body_missing_delimiter(body));
		return (body->err);
	}
	else
		return (body_missing_delimiter(body));
}

t_error	get_body_content(t_body *body)
{
	char	*match_EOL;
	bool	continuation;

	continuation = false;
	while (true)
	{
		if (body->input.data[body->i] == '\0')
		{
			if (body_continuation(body, &continuation).type)
				return (body->err);
		}
		match_EOL = str_chr(body->input.data + body->i, '\n');
		if (get_body_line(body, match_EOL, &body->i).type)
			return (body->err);
		if (is_line_delimiter(body))
			return (body->err);
		if (!string_append(&body->content, &body->line))
			return (body->err = error_sys());
		string_free(&body->line);
	}
}
