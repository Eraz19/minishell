/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specials.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:10:14 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 15:00:07 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPECIALS_H
# define SPECIALS_H

# include "error.h"
# include "libft.h"
# include <stddef.h>
# include <sys/types.h>

/**
 * @struct s_specials
 * @brief Storage for shell special parameters.
 *
 * @var s_specials::source Source string, used for @c $0 input context
 *							(borrowed).
 * @var s_specials::zero @c $0 value (borrowed).
 * @var s_specials::pid Current shell PID.
 * @var s_specials::last_bg_pid Last background PID, or @c -1 when unset.
 * @var s_specials::last_status Last command status.
 */
typedef struct s_specials
{
	/** @brief Source string, used for @c $0 input context (borrowed). */
	t_string	source;
	/** @brief @c $0 value (borrowed). */
	t_string	zero;
	/** @brief Current shell PID. */
	pid_t		pid;
	/** @brief Last background PID, or @c -1 when unset. */
	pid_t		last_bg_pid;
	/** @brief Last command status. */
	int			last_status;
}	t_specials;

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

/**
 * @brief Initialize special parameters with their default state.
 *
 * No heap ownership is assumed at initialization.
 *
 * @param specials Destination structure (borrowed).
 */
void	specials_init(t_specials *specials);

// TODO: doc
void	specials_clear(t_specials *specials);

/**
 * @brief Load special parameters from argv and current shell options.
 *
 * @param specials Destination structure (borrowed).
 * @param argc Argument count.
 * @param argv Argument array (borrowed, read-only).
 * @param start_index Input/output index of the first non-option operand
 *						(borrowed).
 * @return @c ERR_NO, @c ERR_SHELL_NOT_FOUND or @c ERR_OPT_INVALID.
 */
t_error	specials_load(
			t_specials *specials,
			int argc,
			char **argv,
			size_t *start_index);

/**
 * @brief Release special parameter storage.
 *
 * This structure does not own heap allocations.
 *
 * @param specials Structure to clear.
 */
void	specials_free(t_specials *specials);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Read a special parameter into a fresh string.
 *
 * The caller owns @p dst on success and must release it with
 * @ref string_free().
 *
 * @param specials Special values source (borrowed, read-only).
 * @param name Special parameter name.
 * @param dst Initialized destination string (borrowed).
 * @return @c ERR_NO, @c ERR_VAR_NOT_FOUND or @c ERR_LIBC.
 */
t_error	specials_get(const t_specials *specials, char name, t_string *dst);

/**
 * @brief Update the stored last background PID.
 *
 * @param specials Special values source (borrowed).
 * @param value New PID value.
 */
void	specials_set_last_bg_pid(t_specials *specials, pid_t value);

/**
 * @brief Update the stored last command status.
 *
 * @param specials Special values source (borrowed).
 * @param value New status value.
 */
void	specials_set_last_status(t_specials *specials, int value);

#endif
