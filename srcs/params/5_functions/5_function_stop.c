#include "functions_priv.h"
# include <assert.h>

void	function_stop(t_function **function)
{
	assert((*function)->active_count > 0);
	(*function)->active_count--;
	if ((*function)->active_count == 0 && (*function)->pending_free == true)
		function_free(function);
}
