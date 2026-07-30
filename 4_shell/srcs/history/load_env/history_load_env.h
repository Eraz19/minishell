#ifndef HISTORY_LOAD_ENV_H
# define HISTORY_LOAD_ENV_H

# include "history.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

t_error	load_history_max_size_env(t_history *history);

t_error	load_history_path_from_env(t_history *history);

#endif
