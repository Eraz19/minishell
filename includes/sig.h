#ifndef SIG_H
# define SIG_H

# include "sig_priv.h"
# include "params.h"
# include "error.h"
# include <stdbool.h>

// life cycle

void	sig_init(void);
t_error	sig_init_subshell(void);
t_error	sig_load(t_sig_state *sig_state, t_params *params);
void	sig_clear(void);
void	sig_free(void);

// ops

bool	sig_has_pending_trap(int *out_signo);
t_error	sig_process(void);
t_error	sig_process_exit(void);
t_error	sig_set_default(const char *sig_name);
t_error	sig_set_ignore(const char *sig_name);
t_error	sig_set_trap(const char *sig_name, const char *cmd);
t_error	sig_print_all(void);
t_error	sig_print_all_except_default(void);

#endif
