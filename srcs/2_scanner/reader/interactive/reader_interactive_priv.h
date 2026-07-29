#ifndef READER_INTERACTIVE_PRIV_H
# define READER_INTERACTIVE_PRIV_H

# include "libft.h"
# include "error.h"
# include "reader_interactive.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup scanner_reader
 * @brief Fetches the @p mode prompt variable and expands it: @c PS1 first
 *        gets its @c ! history-number expansion (@c !! is a literal
 *        @c ! ), then both prompts get parameter expansion. An expansion
 *        failure is printed and degrades to the raw prompt value with
 *        @c ERR_NO.
 *
 * @param out Receives the expanded prompt, empty when the variable is
 *            unset; initialized by the function (borrowed).
 * @param mode Prompt to build (@ref t_prompt_mode).
 * @return @c ERR_NO on success (including the degraded and unset cases);
 *         @c ERR_LIBC (module allocation failure) on module-produced
 *         failure. Module-external errors (params variable lookup) bubble
 *         through unlisted.
 */
t_error	build_reader_prompt(t_string *out, t_prompt_mode mode);

/**
 * @ingroup scanner_reader
 * @brief Records a signal received during the read in @c $?
 *        (@c 128+signo) — a pending @c SIGINT requests a re-read, a
 *        pending trapped signal is only recorded.
 *
 * @param retry Set to true when a pending @c SIGINT means the interrupted
 *              line must be dropped and read again (borrowed).
 * @return @c ERR_NO on success — the function produces no error of its
 *         own; the @c $? recording failures (params, external) bubble
 *         through unlisted.
 */
t_error	handle_reader_signals(bool *retry);

/**
 * @ingroup scanner_reader
 * @brief Reads one line through readline with @p prompt displayed: makes
 *        stdin blocking again, runs pending signal handlers and traps
 *        before and after the read, and appends the newline readline
 *        stripped.
 *
 * @param out Receives the line; initialized by the function on success,
 *            untouched on failure (borrowed).
 * @param prompt Prompt to display, NULL for none (borrowed, read-only).
 * @param max_retry Ignored-EOF budget (see @c MAX_RETRY_PS1 /
 *                  @c MAX_RETRY_PS2).
 * @return @c ERR_NO on success; @c ERR_VEOF (end of input or budget
 *         exhausted) or @c ERR_LIBC (printed stdin-mode probe failure, or
 *         module allocation failure) on module-produced failure.
 *         Module-external errors (options, sig, EOF newline echo) bubble
 *         through unlisted.
 */
t_error	read_line(t_string *out, const char *prompt, size_t max_retry);

#endif
