#ifndef READER__H
# define READER__H

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
 * @brief Reads one or more continuation lines (PS2 prompt) until a
 *        non-empty one, appends the result to @p res and records it in
 *        the current history entry.
 *
 * @param res Already initialized string the line is appended to
 *            (borrowed).
 * @return @c ERR_VEOF at end of input; @c ERR_LIBC on allocation failure;
 *         @c ERR_SHELL_NOT_FOUND if the shell data is unavailable;
 *         @c ERR_NO on success.
 */
t_error	reader_continuation(t_string *res);

/**
 * @ingroup scanner_reader
 * @brief Reads the whole script file @p path and appends a final newline.
 *
 * @param res String receiving the file content, initialized by the
 *            function and freed on failure (borrowed).
 * @param path Script file path (borrowed, read-only).
 * @return @c ERR_POSIX_CMD_NOT_FOUND (printed) when @p path does not
 *         exist; @c ERR_POSIX_CMD_NOT_EXECUTABLE (printed) when it cannot
 *         be opened for any other reason; @c ERR_POSIX_READ (printed) on a
 *         read error; @c ERR_INTERRUPTED when a signal interrupts a file
 *         operation; @c ERR_LIBC on allocation or close failure;
 *         @c ERR_NO on success.
 */
t_error	reader_file_input(t_string *res, const char *path);

/**
 * @ingroup scanner_reader
 * @brief Saves the previous history entry, then reads prompted lines
 *        (PS1) until a non-empty one and records it in a new history
 *        entry.
 *
 * @param res String receiving the line, initialized by the function and
 *            freed on failure (borrowed).
 * @return @c ERR_VEOF at end of input when the shell must exit;
 *         @c ERR_LIBC on allocation failure; @c ERR_SHELL_NOT_FOUND if
 *         the shell data is unavailable; @c ERR_NO on success.
 */
t_error	reader_new_input(t_string *res);

/**
 * @ingroup scanner_reader
 * @brief Fetches and expands a prompt variable (POSIX.1-2024 XCU 2.5.3):
 *        @c PS1 undergoes exclamation-mark expansion (@c '!' becomes the
 *        history number of the next command, @c "!!" a literal @c '!')
 *        then parameter expansion, @c PS2 parameter expansion only.
 *
 * @note Command substitution and arithmetic expansion are unspecified by
 *       POSIX and not applied.
 * @note An unset or empty variable yields an empty prompt (@c ERR_NO with
 *       an empty @p dst).
 * @note A failed expansion is printed and the unexpanded value is used as
 *       the prompt: POSIX 2.8.1 requires an interactive shell to report
 *       an expansion error without exiting, and leaves the resulting
 *       prompt value unspecified — kept readable as the raw value.
 * @param name Variable name, @c "PS1" or @c "PS2" (borrowed, read-only).
 * @param dst String receiving the expanded prompt, initialized by the
 *            function on every path; the caller owns it (borrowed).
 * @return @c ERR_SHELL_NOT_FOUND or @c ERR_LIBC, raw, if the fetch
 *         fails; @c ERR_NO otherwise (expansion failures are absorbed,
 *         printed here when not already printed by the expander).
 */
t_error	reader_prompt(const char *name, t_string *dst);

/**
 * @ingroup scanner_reader
 * @brief Builds the fully qualified error for an unrecoverable read error
 *        while reading commands (POSIX 2.8.1).
 *
 * @warning Must be called right after the failed read, before errno is
 *          overwritten.
 * @note Prints the specific diagnostic (source and errno message), then
 *       requalifies it as @c ERR_POSIX_READ.
 * @param source Name of the input source for the diagnostic
 *               (borrowed, read-only).
 * @return @c ERR_POSIX_READ (printed).
 */
t_error	reader_read_error(const char *source);

/**
 * @ingroup scanner_reader
 * @brief Low-level prompted read of a single line, newline-terminated.
 *
 * Reads one line via readline() and appends a @c '\n'. On end-of-input it
 * lets the shell decide whether to exit; when the shell must not exit
 * (@c ignoreeof), it keeps prompting instead of surfacing @c ERR_VEOF.
 *
 * @param res String receiving the line, initialized by the function
 *            (borrowed).
 * @param prompt Prompt to display, @c NULL for no prompt
 *               (borrowed, read-only).
 * @return @c ERR_VEOF at end of input when the shell must exit;
 *         @c ERR_LIBC on allocation failure; @c ERR_SHELL_NOT_FOUND if
 *         the shell data is unavailable; @c ERR_NO on success.
 */
t_error	readline_(t_string *res, const char *prompt);

#endif
