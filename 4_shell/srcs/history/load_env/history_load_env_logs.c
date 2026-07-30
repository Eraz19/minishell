#include "logs.h" // DEBUG
#include "history_load_env_priv.h"

void	history_load_file_path_from_logs(const char *path, const char *origin)
{
	print_pass("history file path from $%s           '%s%s%s'\n", BLUE, origin, path, GREY);
}

void	history_load_max_size_from_unset_logs(void)
{
	print_pass("history max size                       default (INFINITE)\n");
}

void	history_load_max_size_from_invalid_logs(void)
{
	print_pass("history max size                       $HISTSIZE invalid, default (INFINITE)\n");
}

void	history_load_max_size_from_out_of_range_logs(ssize_t max)
{
	print_pass("history max size set from $HISTSIZE    %li\n", max);
}

void	history_load_max_size_from_logs(ssize_t max)
{
	print_pass("history max size from $HISTSIZE        default (%li)\n", max);
}
