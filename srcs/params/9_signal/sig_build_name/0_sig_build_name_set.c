#include "sig_build_name_priv.h"

t_error	sig_build_name_set(const char *name, t_string *out_name)
{
	if (!string_init(out_name, 0, name, -1))
		return (error_sys());
	return (error(ERR_NO));
}
