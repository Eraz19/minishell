#include "sig_parse_name_priv.h"

t_error	sig_parse_name_set(
	int signo,
	t_sig_id sig_id,
	int *out_signo,
	t_sig_id *out_sig_id)
{
	*out_signo = signo;
	*out_sig_id = sig_id;
	return (error(ERR_NO));
}
