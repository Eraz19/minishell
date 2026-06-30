#include <fcntl.h>
#include "heredoc.h"
#include "expander_.h"
#include "posix_helpers.h"
#include "quote_removal_.h"
#include "expander_loader_.h"
#include "field_splitting_.h"
#include "expander_expansion_.h"
#include "path_name_expansion_.h"
#include "expander_substitutions_.h"

t_error	expander_expand(t_expansion *expansion, t_expander_args *args)
{
	t_expander	state;

	expander_init(&state, args->role);
	if (expander_load(&state, args).type)
		return (expander_free(&state), state.err);
	if (substitutions(&state).type)
		return (expander_free(&state), state.err);
	if (field_splitting(&state).type)
		return (expander_free(&state), state.err);
	if (path_name_expansion(&state).type)
		return (expander_free(&state), state.err);
	if (quote_removal(&state).type)
		return (expander_free(&state), state.err);
	state.err = expander_loader_extract(&state.fields, expansion);
	return (expander_free(&state), state.err);
}

t_error	read_heredoc_body(t_string *heredoc_file_path, t_string *heredoc_body)
{
	int		fd;
	t_error	err;

	if (!string_init(heredoc_body, 0, NULL, 0))
		return (error_sys());
	err = posix_open(heredoc_file_path->data, O_RDONLY, &fd);
	if (err.type)
		return (err);
	if (!string_read_all(heredoc_body, fd))
		return (err = error_sys(), posix_close(fd), err);
	return (posix_close(fd), err);
}

t_error store_expansion_result_in_heredoc_file(
			t_string *path,
			t_expansion *expansion)
{
	t_error		err;
	t_string	src;
	t_string	heredoc_body;

	if (expansion->len == 1)
	{
		expansion_get(expansion, 0, &src);
		if (!string_init(&heredoc_body, 0, src.data, (long)src.len))
			return (error_sys());
		err = heredoc_save_body_in_file(path, &heredoc_body);
		if (err.type != ERR_NO)
			return (err);
	}
	else
		return (error(ERR_EXP_TOO_MANY_FIELDS));
	return (error(ERR_NO));
}
