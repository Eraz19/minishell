#include "logs.h" // DEBUG
#include "history_adapter.h"

void	success_history_adapter_add_log(t_history_adapter *history_adapter)
{
	print_pass("entries uploaded to readline           %i\n", (int)history_adapter->count);
}
