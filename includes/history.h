#ifndef HISTORY_H
# define HISTORY_H

# include "error.h"
# include "libft.h"
# include "history_list_.h"
# include "history_file_.h"
# include "history_readline_.h"

typedef struct s_history
{
	t_error			err;
	t_history_file	file;
	t_history_list	list;
	t_history_rl	rl_history;
	t_string		current_input;
}	t_history;

void	history_init(t_history *state);
void	history_free(t_history *state);
t_error	history_load(t_history *state);

t_error	history_save(void);
t_error	history_save_entry(void);
t_error	history_append_to_entry(t_string *entry);

#endif
