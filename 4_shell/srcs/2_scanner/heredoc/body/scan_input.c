#include "reader.h"
#include "heredoc_body.h"
#include "heredoc_body_priv.h"

bool	is_line_delimiter(t_body *body)
{
	if (body->mode == HEREDOC_MODE_TAB_STRIP)
		string_trim_leading(&body->line, '\t');
	return (string_cmp(&body->line, &body->delim));
}

t_error	extract_body_line(t_body *body, char *EOL, size_t *i)
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

t_error	read_body_ps2(t_body *body)
{
	body->err = reader_read_PS2(&body->input);
	if (body->err.type == ERR_VEOF || body->err.type == ERR_POSIX_SYNTAX)
		error_missing_delimiter(body);
	return (body->err);
}

t_error	scan_input_for_heredoc_body(t_body *body)
{
	char	*match_EOL;

	while (true)
	{
		if (body->input.data[body->i] == '\0' && read_body_ps2(body).type)
			return (body->err);
		match_EOL = str_chr(body->input.data + body->i, '\n');
		if (extract_body_line(body, match_EOL, &body->i).type)
			return (body->err);
		if (is_line_delimiter(body))
			return (body->err);
		if (!string_append(&body->content, &body->line))
			return (body->err = error_sys());
		string_free(&body->line);
	}
}
