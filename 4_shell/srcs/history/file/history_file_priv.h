#ifndef HISTORY_FILE_PRIV_H
# define HISTORY_FILE_PRIV_H

# include "history_file.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

t_error	read_history_file(t_history_file *history_file);

t_error	open_history_file(int *out, const char *path, int flags);

/* ************************************************************************* */
/*                                   ERROR                                   */
/* ************************************************************************* */

t_error	on_history_file_open_error(t_error err, const char *path);

t_error	on_history_file_read_error(t_error err, const char *path);

t_error	on_history_file_write_error(t_error err, const char *path);

/* ************************************************************************* */
/*                                   LOGS                                    */
/* ************************************************************************* */

void	empty_history_file_load_log(void);

void	history_file_save_end_log(t_history_file *history_file);

void	history_file_save_start_log(t_history_file *history_file);

void	success_history_file_load_log(t_history_file *history_file);

#endif
