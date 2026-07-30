#include "logs.h" // DEBUG
#include "history_priv.h"

void	history_load_start_logs(const char *func_name)
{
	print_title("%s()", func_name);
}

void	history_load_end_logs(const char *func_name)
{
	print_result("%s()", func_name);
}
