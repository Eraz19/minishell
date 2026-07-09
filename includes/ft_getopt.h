#ifndef FT_GETOPT_H
# define FT_GETOPT_H

# include "error.h"
# include "libft.h"
# include <stdbool.h>
# include <stddef.h>

/*
⚠️ TODO: in each builtin (if doc doesn't specifiy anything else): call undefined_behaviour() when "use of conflicting mutually-exclusive arguments" cf 12.1:8.
---
⚠️ TODO: XBD 12.2:
	- Guideline 7
	- Guideline 8
*/

/* ************************************************************************* */
/*                                   INPUT                                   */
/* ************************************************************************* */

/**
 * @struct s_option_with_arg
 * @brief Specification for one option that accepts an argument.
 *
 * @var s_option_with_arg::sign Accepted option prefix, either @c '-' or @c '+'.
 * @var s_option_with_arg::flag Option letter matched after @p sign.
 * @var s_option_with_arg::arguments_valids NULL-terminated array of accepted
 *      argument C-strings (borrowed, read-only).
 * @var s_option_with_arg::arguments_are_optional True when the option argument
 *      may be omitted, false when it is mandatory.
 */
typedef struct s_option_with_arg
{
	char		sign;								// '+' / '-'
	char		flag;
	const char	**arguments_valids;					// NULL-terminated
	bool		arguments_are_optional;
}	t_getopt_flag_with_arg;

/**
 * @struct s_getopt_in
 * @brief Parsing specification consumed by @ref ft_getopt().
 *
 * @var s_getopt_in::builtin_name Diagnostic prefix forwarded to
 *      @ref error_print() when @ref ft_getopt() reports a user-facing parsing
 *      error (borrowed, read-only).
 * @var s_getopt_in::valid_minus_flags NULL-terminated C-string listing accepted
 *      short flags introduced by @c '-' or @c NULL when none are accepted
 *      (borrowed, read-only).
 * @var s_getopt_in::valid_plus_flags NULL-terminated C-string listing accepted
 *      short flags introduced by @c '+' or @c NULL when none are accepted
 *      (borrowed, read-only).
 * @var s_getopt_in::options_with_arg Array describing options that accept an
 *      argument; entries may reuse the same @c flag when their @c sign differs
 *      (borrowed, read-only).
 * @var s_getopt_in::options_with_arg_count Number of entries stored in
 *      @ref s_getopt_in::options_with_arg.
 * @var s_getopt_in::single_delimiter True when a lone @c - stops option
 *      parsing, false when only @c -- acts as an explicit delimiter.
 * @var s_getopt_in::ub_on_repeated_flags True to report repeated no-argument
 *      flags as undefined behaviour, false to keep them accepted.
 */
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

/**
 * @struct s_getopt_option
 * @brief One parsed option emitted by @ref ft_getopt().
 *
 * @var s_getopt_option::sign Original option prefix, either @c '-' or @c '+'.
 * @var s_getopt_option::flag Parsed option letter.
 * @var s_getopt_option::argument Borrowed canonical argument C-string selected
 *      from the input specification, or @c NULL when the option has no
 *      argument (borrowed, read-only).
 */
typedef struct s_getopt_option
{
	char		sign;		// '-' / '+'
	char		flag;		// 'a'...
	const char	*argument;	// NULL / argument
}	t_getopt_option;

/**
 * @struct s_getopt_out
 * @brief Parsed options and operand boundary produced by @ref ft_getopt().
 *
 * @var s_getopt_out::options Output @ref t_vector of @ref t_getopt_option
 *      entries initialized by @ref ft_getopt() and owned by the caller.
 * @var s_getopt_out::first_operand_index Index of the first operand in
 *      @p argv after option parsing stops.
 */
typedef struct s_getopt_out
{
	t_vector	options;
	size_t		first_operand_index;
}	t_getopt_out;

/* ************************************************************************* */
/*                                  FUNCTION                                 */
/* ************************************************************************* */

/**
 * @brief Parse short @c + and @c - options from @p argv.
 *
 * @note The function initializes @p out->options and, on success, the caller
 *       must release it with @c vector_free(&out->options, NULL).
 * @note This function always prints a diagnostic before returning an error.
 *
 * @param argc Argument count.
 * @param argv Argument array to parse, with the command name at index 0
 *             (borrowed, read-only).
 * @param input Parsing specification (borrowed, read-only).
 * @param out Destination initialized by the function on entry and filled on
 *            success (borrowed).
 * @return @c ERR_INVALID_USAGE @c ERR_UB or @c ERR_LIBC.
 */
t_error	ft_getopt(int argc, char **argv, t_getopt_in *input, t_getopt_out *out);

/* ************************************************************************* */
/*                                    DEBUG                                  */
/* ************************************************************************* */

/**
 * @brief Dump one @ref t_getopt_in description for debugging.
 *
 * @param in Input specification to print (borrowed, read-only).
 */
void	ft_getopt_dump_in(t_getopt_in *in);

/**
 * @brief Dump one @ref t_getopt_out result for debugging.
 *
 * @param out Parsed output to print (borrowed, read-only).
 */
void	ft_getopt_dump_out(t_getopt_out *out);

/**
 * @brief Dump both the parsing specification and the parsed output.
 *
 * @param in Input specification to print (borrowed, read-only).
 * @param out Parsed output to print (borrowed, read-only).
 */
void	ft_getopt_dump_all(t_getopt_in *in, t_getopt_out *out);

#endif
