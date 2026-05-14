#ifndef SPECIALS_H
# define SPECIALS_H

# include "error.h"
# include <stddef.h>
# include <sys/types.h>

typedef struct s_specials
{
	char				*zero;			// $0
	char				*source;		// (internal, can be NULL)
	pid_t				pid;			// $$
	pid_t				last_bg_pid;	// $!
	int					last_status;	// $?
}	t_specials;

void	specials_init(t_specials *specials);

// @ret ERR_SHELL_NOT_FOUND / ERR_OPTION_INVALID
t_error	specials_load(
	t_specials *specials,
	int argc,
	char **argv,
	size_t options_count);
	
void	specials_free(t_specials *specials);

#endif
