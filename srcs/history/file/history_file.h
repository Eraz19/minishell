#ifndef HISTORY_FILE_H
# define HISTORY_FILE_H

# include "libft.h"
# include "error.h"
# include "history_list.h"

/* ************************************************************************* */
/*                                  TYPES                                    */
/* ************************************************************************* */

typedef struct s_history_file
{
	t_error		err;
	t_string 	path;
	t_string	content;
	size_t		loaded_count;
}	t_history_file;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

void	history_file_init(t_history_file *history_file);

void	history_file_free(t_history_file *history_file);

t_error	history_file_load(t_history_file *history_file, t_history_list *history_list, ssize_t max);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

t_error	write_history_file(t_history_file *history_file);

#endif
