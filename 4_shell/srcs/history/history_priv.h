#ifndef HISTORY_PRIV_H
# define HISTORY_PRIV_H

# include "error.h"
# include "history.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

t_error	build_saving_file_content(t_history *history, size_t start);

/* ************************************************************************* */
/*                                 ERROR                                     */
/* ************************************************************************* */

t_error	requalify_history_error(t_error err);

/* ************************************************************************* */
/*                                   LOGS                                    */
/* ************************************************************************* */

void	history_load_end_logs(const char *func_name);

void	history_load_start_logs(const char *func_name);

#endif
