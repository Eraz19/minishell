#ifndef SPECIALS_H
# define SPECIALS_H

# include "error.h"
# include <stddef.h>
# include <sys/types.h>

typedef struct s_specials
{
	char				*source;		// (internal, can be NULL)
	char				*zero;			// $0 (NOT editable after instanciation)
	pid_t				pid;			// $$ (NOT editable after instanciation)
	pid_t				last_bg_pid;	// $!
	long				last_status;	// $?
}	t_specials;

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

void	specials_init(t_specials *specials);

// @ret ERR_NO / ERR_SHELL_NOT_FOUND / ERR_OPTION_INVALID.
t_error	specials_load(
	t_specials *specials,
	int argc,
	char **argv,
	size_t *start_index);
	
void	specials_free(t_specials *specials);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

// @warning: *dst is owned by caller, he must free it.
// @ret ERR_NO / ERR_VAR_NOT_FOUND / ERR_LIBC.
t_error	specials_get(const t_specials *specials, char name, char **dst);

// @note: only available for '!' and '?'.
// @ret ERR_NO / ERR_VAR_NOT_FOUND.
t_error	specials_set(t_specials *specials, char name, long value);

/* ************************************************************************* */
/*                                   DEBUG                                   */
/* ************************************************************************* */

void	specials_dump_all(void);

#endif
