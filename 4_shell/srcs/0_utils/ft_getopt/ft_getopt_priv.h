/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt_priv.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:47:55 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:51:07 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GETOPT_PRIV_H
# define FT_GETOPT_PRIV_H

# include "ft_getopt.h"
# include "error.h"

/**
 * @struct s_getopt_state
 * @brief Mutable parsing cursor shared by the @ref ft_getopt() helpers.
 *
 * @var s_getopt_state::argc Total argument count currently being parsed.
 * @var s_getopt_state::argv Argument array currently being parsed (borrowed,
 *      read-only).
 * @var s_getopt_state::arg_i Current argument index in @p argv.
 * @var s_getopt_state::char_i Current character offset inside
 *      @p argv[arg_i].
 * @var s_getopt_state::in Parsing specification forwarded to helper functions
 *      (borrowed).
 * @var s_getopt_state::out Output accumulator filled by helper functions
 *      (borrowed).
 */
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

/**
 * @brief Append one parsed option to @p state->out->options.
 *
 * @param state Current parsing state (borrowed).
 * @param src Parsed option to copy into the output vector (borrowed, read-only).
 * @return @c ERR_NO or @c ERR_LIBC.
 */
t_error	getopt_add_option(t_getopt_state *state, t_getopt_option *src);

/**
 * @brief Build and print one option-parsing diagnostic.
 *
 * @note The returned error has already been printed through @ref error_print().
 *
 * @param state Current parsing state used to recover the builtin name
 *              (borrowed, read-only).
 * @param flag Option letter that triggered the diagnostic.
 * @param arg Invalid option argument to display, or @c NULL when not
 *            applicable (borrowed, read-only).
 * @param err_type Error kind to report.
 * @return Printed error descriptor with type @p err_type.
 */
t_error	getopt_err(
			const t_getopt_state *state,
			char flag,
			const char *arg, t_error_type err_type);

/* ************************************************************************* */
/*                                 OPTIONS                                   */
/* ************************************************************************* */

/**
 * @brief Parse the current clustered option argument stored in @p state.
 *
 * @note Option-usage errors returned by this function have already been printed
 *       through @ref getopt_err().
 *
 * @param state Current parsing state updated in place (borrowed).
 * @return @c ERR_NO, @c ERR_OPT_INVALID, @c ERR_OPT_MISSING_ARG,
 *         @c ERR_OPT_INVALID_ARG or @c ERR_LIBC.
 */
t_error	getopt_process_arg(t_getopt_state *state);

#endif
