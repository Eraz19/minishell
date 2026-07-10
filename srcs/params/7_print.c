#include "params.h"
# include <assert.h>	// DEBUG

t_error params_print(t_params_print_mode mode)
{
	assert(mode == PARAMS_PRINT_EXPORT || mode == PARAMS_PRINT_READONLY
		|| mode == PARAMS_PRINT_SET);
	return var_print((t_var_print_mode)mode);
}
