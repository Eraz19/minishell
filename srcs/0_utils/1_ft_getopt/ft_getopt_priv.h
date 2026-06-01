#ifndef FT_GETOPT_PRIV_H
# define FT_GETOPT_PRIV_H

# include "ft_getopt.h"

typedef struct s_getopt_state
{
	int				argc;
	char			**argv;
	int				arg_i;
	size_t			char_i;
	t_getopt_in		*in;
	t_getopt_out	*out;
}	t_getopt_state;

/* ************************************************************************* */
/*                                   UTILS                                   */
/* ************************************************************************* */

// @ret ERR_LIBC
t_error	getopt_add_option(t_getopt_state *state, t_getopt_option *src);

// @ret error
t_error	getopt_err(
	t_getopt_state *state,
	char flag,
	const char *arg, t_error error);

/* ************************************************************************* */
/*                                 OPTIONS                                   */
/* ************************************************************************* */

// @ret ERR_OPT_INVALID / ERR_OPT_MISSING_ARG / ERR_OPT_INVALID_ARG / ERR_LIBC
t_error	getopt_process_arg(t_getopt_state *state);

#endif
