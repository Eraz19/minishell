#ifndef FT_GETOPT_H
# define FT_GETOPT_H

# include "error.h"
# include "libft.h"
# include <stdbool.h>
# include <stddef.h>

/*
⚠️ TODO: in each builtin (if doc doesn't specifiy anything else): call undefined_behaviour() when "use of conflicting mutually-exclusive arguments" cf 12.1:8.
---
⚠️ XBD 12.2:
	- Guideline 7
	- Guideline 8
*/

/* ************************************************************************* */
/*                                   INPUT                                   */
/* ************************************************************************* */

typedef struct s_option_with_arg
{
	char		sign;								// '+' / '-'
	char		flag;
	const char	**arguments_valids;					// NULL-terminated
	bool		arguments_are_optional;
}	t_getopt_flag_with_arg;

typedef struct s_getopt_in
{
	const char				*builtin_name;			// used to print error logs
	const char				*valid_minus_flags;		// can be NULL
	const char				*valid_plus_flags;		// can be NULL
	t_getopt_flag_with_arg	*options_with_arg;		// multiple options_with_arg can have the same starting flag if they don't have the same sign
	size_t					options_with_arg_count;
	bool					single_delimiter;		// '-' will be treated as end of options
	bool					ub_on_repeated_flags;	// call undefined_behaviour() when "an option that does not have option-arguments is repeated" cf 12.1:3.
}	t_getopt_in;

/* ************************************************************************* */
/*                                  OUTPUT                                   */
/* ************************************************************************* */

typedef struct s_getopt_option
{
	char		sign;		// '-' / '+'
	char		flag;		// 'a'...
	const char	*argument;	// NULL / argument
}	t_getopt_option;

typedef struct s_getopt_out
{
	t_vector	options;
	size_t		first_operand_index;
}	t_getopt_out;

/* ************************************************************************* */
/*                                  FUNCTION                                 */
/* ************************************************************************* */

// @warning: caller must free out->options with vector_free()
// @ret ERR_OPT_INVALID / ERR_OPT_MISSING_ARG / ERR_OPT_INVALID_ARG /
//		ERR_UNDEFINED_BEHAVIOUR / ERR_LIBC
t_error	ft_getopt(int argc, char **argv, t_getopt_in *input, t_getopt_out *out);

/* ************************************************************************* */
/*                                    DEBUG                                  */
/* ************************************************************************* */

void	ft_getopt_dump_in(t_getopt_in *in);
void	ft_getopt_dump_out(t_getopt_out *out);
void	ft_getopt_dump_all(t_getopt_in *in, t_getopt_out *out);

#endif
