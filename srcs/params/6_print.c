#include "params.h"

t_error params_print(t_params_print_mode mode)
{
	return var_print((t_var_print_mode)mode);
}
