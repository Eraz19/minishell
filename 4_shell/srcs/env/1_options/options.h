/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:09:46 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 21:33:54 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONS_H
# define OPTIONS_H

# include "error.h"
# include "libft.h"
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

typedef enum e_option
{
	OPT_EXPORT_ALL = 1u << 0,
	OPT_NOTIFY = 1u << 1,
	OPT_NOCLOBBER = 1u << 2,
	OPT_ERREXIT = 1u << 3,
	OPT_NOGLOB = 1u << 4,
	OPT_CMD_HASH = 1u << 5,
	OPT_INTERACTIVE = 1u << 6,
	OPT_MONITOR = 1u << 7,
	OPT_NOEXEC = 1u << 8,
	OPT_NOUNSET = 1u << 9,
	OPT_VERBOSE = 1u << 10,
	OPT_XTRACE = 1u << 11,
	OPT_CMD_STRING = 1u << 12,
	OPT_STDIN_INPUT = 1u << 13,
	OPT_IGNOREEOF = 1u << 14,
	OPT_NOLOG = 1u << 15,
	OPT_PIPEFAIL = 1u << 16,
	OPT_VI = 1u << 17,
	OPT_SINGLE_COUNT = 14
}	t_option;

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

/**
 * @brief Placeholder cleanup for an option bitset.
 *
 * The bitset owns no heap memory and nothing is released.
 *
 * @param options Bitset to clear (borrowed).
 */
void		options_free(t_option *options);

// TODO: doc
void		options_clear(t_option *options);

/**
 * @brief Reset an option bitset to its empty state.
 *
 * @param options Destination bitset (borrowed).
 */
void		options_init(t_option *options);

/**
 * @brief Parse shell options from argv.
 *
 * @param options Destination bitset (borrowed).
 * @param argc Argument count.
 * @param argv Argument vector (borrowed, read-only).
 * @param start_index Output index of the first non-option operand (borrowed).
 * @return @c ERR_OPT_INVALID, @c ERR_OPT_MISSING_ARG, @c ERR_OPT_INVALID_ARG
 *         or @c ERR_LIBC on failure.
 */
t_error		options_load(
				t_option *options,
				int argc,
				char **argv,
				size_t *start_index);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Set or clear a specific option bit in a bitset.
 *
 * @param options Bitset to modify (borrowed).
 * @param option Option bit to change.
 * @param on True to enable the bit, false to clear it.
 */
void		option_set(t_option *options, t_option option, bool on);

/**
 * @brief Check whether an option is active in the current shell state.
 *
 * @param option Option bit to query.
 * @param out Receives the active state (borrowed).
 * @return @c ERR_INTERNAL on failure.
 */
t_error		option_is_active(t_option option, bool *out);

/**
 * @brief Check whether an option is active in a provided bitset.
 *
 * @param options Bitset to inspect.
 * @param option Option bit to query.
 * @return True when the bit is set.
 */
bool		option_is_active_in(t_option options, t_option option);

/**
 * @brief Serialize active options into a fresh string.
 *
 * The caller owns @p dst on success and must release it with
 * @ref string_free().
 *
 * @param options Bitset to serialize.
 * @param dst Initialized destination string (borrowed).
 * @return @c ERR_NO or @c ERR_LIBC.
 */
t_error		options_get(t_option options, t_string *dst);

#endif
