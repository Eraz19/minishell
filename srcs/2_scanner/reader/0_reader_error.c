#include "reader_.h"

t_error	reader_read_error(t_error err, const char *source)
{
	err = error_print(err, "scanner", source, "read error", NULL, NULL);
	err.type = ERR_POSIX_READ;
	return (err);
}
