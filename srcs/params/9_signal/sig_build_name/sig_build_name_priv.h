#ifndef SIG_BUILD_NAME_PRIV_H
# define SIG_BUILD_NAME_PRIV_H

# include "sig_priv.h"
# include "error.h"

t_error	sig_build_name_set(const char *name, t_string *out_name);
t_error	sig_build_name_2(t_sig_id sig_id, t_string *out_name);

#endif
