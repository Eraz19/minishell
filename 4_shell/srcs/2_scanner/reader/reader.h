/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:15:05 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:59:45 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H

# include <stdio.h>
# include "error.h"
# include "libft.h"

/** @defgroup scanner_reader Scanner reader
 *  @brief Fetches raw shell input: prompted lines, script files, stdin.
 *
 *  The reader tolerates an unset @c PS1 / @c PS2 (empty prompt) and
 *  requalifies its POSIX-mandated failures itself, at the most specific
 *  point: a script file that cannot be opened becomes
 *  @c ERR_POSIX_CMD_NOT_FOUND / @c ERR_POSIX_CMD_NOT_EXECUTABLE and an
 *  unrecoverable read error becomes @c ERR_POSIX_READ, both printed with
 *  the failing source and the errno message.
 */

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup scanner_reader
 * @brief Reads the whole script file at @p path into @p out, requalifying
 *        an opening failure into the POSIX invocation error (printed,
 *        @c $? set) and a read failure into @c ERR_POSIX_READ (printed).
 *
 * @param out Receives the file content; must not hold owned text (it is
 *            re-initialized, not freed); initialized by the function, and
 *            freed by the function on read failure, untouched when opening
 *            fails (borrowed).
 * @param path Path of the script file (borrowed, read-only).
 * @return @c ERR_NO on success; @c ERR_POSIX_CMD_NOT_FOUND (printed, file
 *         missing), @c ERR_POSIX_CMD_NOT_EXECUTABLE (printed, any other
 *         opening failure, including a directory operand) or
 *         @c ERR_POSIX_READ (printed) on failure; the @ref file_check
 *         errors (external) pass through unqualified.
 */
t_error	reader_read_file(t_string *out, const char *path);

/**
 * @ingroup scanner_reader
 * @brief Prompts @c PS1 and reads one interactive command line, with its
 *        trailing newline appended, saving it as a new history entry.
 *
 * @warning May return an error recorded by an earlier history operation:
 *          the history state error is sticky (external, history module).
 *
 * @param out Receives the line; initialized by the function, freed by the
 *            function on failure (borrowed).
 * @return @c ERR_NO on success; @c ERR_VEOF (end of input, or the retry
 *         budget of @c MAX_RETRY_PS1 ignored EOFs is exhausted) or
 *         @c ERR_LIBC (module allocation / libc failure) on
 *         module-produced failure. Module-external errors (options,
 *         params, history, sig, EOF newline echo) bubble through
 *         unlisted.
 */
t_error	reader_read_ps1(t_string *out);

/**
 * @ingroup scanner_reader
 * @brief Prompts @c PS2, reads one continuation line and appends it, with
 *        its trailing newline, to @p out; appends it to the current
 *        history entry as well.
 *
 * @note @c ERR_NO guarantees at least one character was appended to
 *       @p out; when the shell is not interactive nothing is read and
 *       @c ERR_VEOF is returned with @p out untouched. Callers rely on
 *       this to tell "input grew" from "no more input".
 *
 * @param out Current input to grow; must be initialized by the caller
 *            (borrowed).
 * @return @c ERR_NO on success; @c ERR_POSIX_SYNTAX (unprinted, shell not
 *         interactive: no continuation is possible), @c ERR_VEOF
 *         (interactive end of input) or @c ERR_LIBC (module allocation /
 *         libc failure) on module-produced failure. Module-external
 *         errors (options, params, history, sig, EOF newline echo)
 *         bubble through unlisted.
 */
t_error	reader_read_ps2(t_string *out);

/**
 * @ingroup scanner_reader
 * @brief Slurps all of stdin into @p out (non-interactive stdin mode).
 *
 * @param out Receives the input; must not hold owned text (it is
 *            re-initialized, not freed); initialized by the function,
 *            freed by the function on failure (borrowed).
 * @return @c ERR_NO on success; @c ERR_POSIX_READ (printed) on failure.
 */
t_error	reader_read_stdin(t_string *out);

/**
 * @ingroup scanner_reader
 * @brief Readline character hook: reads one byte from stdin, turning a
 *        read interrupted by a pending @c SIGINT into @c EOF so readline
 *        returns instead of blocking.
 *
 * @param stream Ignored; readline passes its input stream (borrowed,
 *               read-only).
 * @return The byte read, or @c EOF on end of input, pending @c SIGINT or
 *         read error.
 */
int		reader_readline_hook(FILE *stream);

#endif
