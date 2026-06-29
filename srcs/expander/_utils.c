#include <fcntl.h>
#include <stdlib.h>
#include "expander_.h"
#include "posix_helpers.h"
#include "quote_removal_.h"
#include "expander_loader_.h"
#include "field_splitting_.h"
#include "path_name_expansion_.h"
#include "expander_substitutions_.h"

t_error	expander_expand(char ***expansion, t_expander_args *args)
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

t_error	read_heredoc_body(t_buff *heredoc_file_path, t_buff *heredoc_body)
{
	int		fd;
	t_error	err;
	char	*path_str;

	if (!buff_init(heredoc_body, 0, NULL, 0))
		return (error_sys());
	path_str = buff_get_string(heredoc_file_path);
	if (path_str == NULL)
		return (error_sys());
	err = posix_open(path_str, O_RDONLY, &fd);
	if (err.type)
		return (free(path_str), err);
	free(path_str);
	if (!buff_read_all(heredoc_body, fd))
		return (err = error_sys(), posix_close(fd), err);
	return (posix_close(fd), err);
}
