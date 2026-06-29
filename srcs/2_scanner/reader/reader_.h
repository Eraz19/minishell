#ifndef READER__H
# define READER__H

# include "error.h"
# include "libft.h"

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
t_error	readline_(t_string *res, const char *prompt);

t_error	reader_new_input(t_string *res);

t_error	reader_continuation(t_string *res);

t_error	reader_file_input(t_string *res, const char *path);

#endif
