#include "write_c_file_priv.h"
#include "generator_serialize_priv.h"

#define VAR_START		"\tstatic const "
#define VAR_BRACK_START	" = {"
#define VAR_BRACK_END	"};\n"

#define BRACK_START		"{"
#define BRACK_END		"},"
#define BRACK_LAST		"}"

bool	generator_write_c_var_start(int c_fd, const char *var_def)
{
	if (!generator_write(c_fd, VAR_START))
		return (false);
	if (!generator_write(c_fd, var_def))
		return (false);
	return (generator_write(c_fd, VAR_BRACK_START));
}

bool	generator_write_c_var_end(int c_fd)
{
	return (generator_write(c_fd, VAR_BRACK_END));
}

bool	generator_write_brack_start(int c_fd)
{
	return (generator_write(c_fd, BRACK_START));
}

bool	generator_write_brack_end(int c_fd)
{
	return (generator_write(c_fd, BRACK_END));
}

bool	generator_write_brack_last(int c_fd)
{
	return (generator_write(c_fd, BRACK_LAST));
}
