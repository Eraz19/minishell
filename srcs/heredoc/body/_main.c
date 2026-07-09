#include <fcntl.h>
#include "body_.h"
#include "posix_helpers.h"

t_lexer_context_args	body_context_rules(void)
{
	t_lexer_context_args	res;

	res.quoting = NULL;
	res.is_quoting = NULL;
	res.unescaped_args = NULL;
	res.escape = body_escape;
	res.is_end = is_context_none_ending;
	res.unescaped = body_unescape;
	res.expansion = lexer_rule_expansion;
	res.is_expansion = is_substitution_context;
	return (res);
}

t_error	read_body_file(t_string *out, const t_string *path)
{
	int		fd;
	t_error	err;

	if (!string_init(out, 0, NULL, 0))
		return (error_sys());
	err = posix_open(path->data, O_RDONLY, &fd);
	if (err.type == ERR_LIBC)
		return (error_print(err, "heredoc", path->data, NULL, NULL));
	if (err.type)
		return (err);
	if (!string_read_all(out, fd))
		return (err = error_print(error_sys(), "heredoc", path->data,
				NULL, NULL), posix_close(fd), string_free(out), err);
	return (posix_close(fd), err);
}

t_error	save_body_in_file(const t_string *path, t_string *body)
{
	int		fd;
	t_error	err;
	int		o_flags;

	o_flags = O_WRONLY | O_CREAT | O_TRUNC;
	err = posix_open_with_mode(path->data, o_flags, 0600, &fd);
	if (err.type == ERR_LIBC)
		return (error_print(err, "heredoc", path->data, NULL, NULL));
	if (err.type)
		return (err);
	err = posix_write(fd, body->data, body->len);
	if (err.type == ERR_POSIX_WRITE)
		err = error_print(err, "heredoc", path->data, NULL, NULL);
	if (err.type == ERR_NO)
		err = posix_close(fd);
	else
		(void)posix_close(fd);
	return (err);
}
