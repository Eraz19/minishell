#ifndef READER__H
# define READER__H

# include "error.h"

/**
 * @ingroup scanner
 * @brief Reads one here-document body line, appending it to @p res.
 *
 * Prompts for and reads a line; if @p *res is NULL it becomes the line,
 * otherwise the line is appended. The caller owns the resulting string.
 *
 * @param res In/out heap string holding the accumulated body (owned).
 * @return ERR_NO on success, ERR_NULL_ARGS if @p res is NULL, ERR_VEOF at a
 *         non-interactive end-of-input, or ERR_LIBC on allocation failure.
 */
t_error	reader_heredoc(char **res);

/**
 * @ingroup scanner
 * @brief Reads a fresh command line from standard input (primary prompt).
 *
 * Sets @p *res to a newly allocated line (newline-terminated). An empty line
 * yields @p *res == NULL with ERR_NO, so the caller can treat it as a no-op.
 *
 * @param res Out heap string receiving the line (owned), or NULL if empty.
 * @return ERR_NO on success, ERR_NULL_ARGS if @p res is NULL, ERR_VEOF at a
 *         non-interactive end-of-input, or ERR_LIBC on allocation failure.
 */
t_error	reader_new_input(char **res);

/**
 * @ingroup scanner
 * @brief Reads a continuation line and appends it to @p res (secondary prompt).
 *
 * Used when a construct spans lines (an open quote or a trailing backslash).
 * The caller owns the resulting string.
 *
 * @param res In/out heap string holding the input being continued (owned).
 * @return ERR_NO on success, ERR_NULL_ARGS if @p res is NULL, ERR_VEOF at a
 *         non-interactive end-of-input, or ERR_LIBC on allocation failure.
 */
t_error	reader_continuation(char **res);

/**
 * @ingroup scanner
 * @brief Reads an entire file into @p res.
 *
 * Opens @p path, reads it fully into a newly allocated string and closes it.
 * The caller owns the resulting string.
 *
 * @param res Out heap string receiving the file contents (owned).
 * @param path File to read (borrowed).
 * @return ERR_NO on success, ERR_NULL_ARGS if @p path is NULL, ERR_OPEN_FILE
 *         if it cannot be opened, or ERR_LIBC on allocation failure.
 */
t_error	reader_file_input(char **res, const char *path);

/**
 * @ingroup scanner
 * @brief Low-level prompted read of a single line, newline-terminated.
 *
 * Reads one line via readline(), appends a '\n', and returns it through
 * @p res. On end-of-input it lets the shell decide whether to exit; in a
 * non-interactive session that cannot exit, it surfaces ERR_VEOF instead of
 * looping.
 *
 * @param res Out heap string receiving the line (owned).
 * @param prompt Prompt string to display (borrowed).
 * @return ERR_NO on success, ERR_VEOF at a non-interactive end-of-input, or
 *         ERR_LIBC on allocation failure.
 */
t_error	readline_(char **res, const char *prompt);

#endif
