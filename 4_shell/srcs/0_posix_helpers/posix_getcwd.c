#include "error.h"
#include "posix_helpers.h"
#include <errno.h>
#include <stdint.h>
#include <unistd.h>

#define BUFF_INITIAL_CAP	128

static inline t_error	getcwd_grow_size(size_t *size)
{
	if (*size > SIZE_MAX / 2)
		return (error(ERR_SIZE_MAX_REACHED));
	*size *= 2;
	return (error(ERR_NO));
}

t_error	posix_getcwd(t_string *dst)
{
	size_t	size;
	t_error	err;

	size = BUFF_INITIAL_CAP;
	while (true)
	{
		if (!string_init(dst, size, NULL, 0))
			return (error_sys());
		if (getcwd(dst->data, size))
		{
			dst->len = str_len(dst->data);
			return (error(ERR_NO));
		}
		err = error_sys();
		string_free(dst);
		if (err.saved_errno != ERANGE)
			return (err);
		err = getcwd_grow_size(&size);
		if (err.type)
			return (err);
	}
}
