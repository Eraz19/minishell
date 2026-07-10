#include "redirector_priv.h"
#include <unistd.h>
# include <assert.h>

t_error	redirect_resolve_location(t_redir *redir)
{
	char		*content_start;
	size_t		last_char_index;
	char		last_char;
	bool		res;
	t_error		err;

	assert(redir->is_location == true);
	content_start = redir->expanded_location.data + 1;
	last_char_index = redir->expanded_location.len - 1;
	last_char = redir->expanded_location.data[last_char_index];
	redir->expanded_location.data[last_char_index] = '\0';
	res = redirect_parse_fd(content_start, &redir->fd);
	if (res == true)
		err = error(ERR_NO);
	else
		err = error_print(error(ERR_REDIRECTION), REDIRECTOR_MODULE_NAME,
			"io_location is not a valid file descriptor", NULL,
			"'%s' expanded from '%s'",
			content_start, redir->location->value.data);
	redir->expanded_location.data[last_char_index] = last_char;
	return (err);
}
