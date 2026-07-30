#ifndef READER_PRIV_H
# define READER_PRIV_H

# include "libft.h"
# include "error.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup scanner_reader
 * @brief Opens @p path, reads it whole into @p out and closes it; an
 *        opening failure is requalified into the POSIX invocation error
 *        (printed, @c $? set through @ref env_set_last_status) and a
 *        read failure into @c ERR_POSIX_READ through @ref on_read_error.
 *
 * @param out Receives the file content; must not hold owned text (it is
 *            re-initialized, not freed); initialized by the function, and
 *            freed by the function on read failure, untouched when opening
 *            fails (borrowed). A close failure after a successful read is
 *            absorbed (the content is already whole in memory).
 * @param path Path of the file to read (borrowed, read-only).
 * @return @c ERR_NO on success; @c ERR_POSIX_CMD_NOT_FOUND (printed, file
 *         missing: ENOENT / ENOTDIR), @c ERR_POSIX_CMD_NOT_EXECUTABLE
 *         (printed, any other opening failure, including a directory
 *         operand) or @c ERR_POSIX_READ (printed) on failure; the
 *         @ref file_check errors pass through unqualified.
 */
t_error	read_file(t_string *out, const char *path);

/* ************************************************************************* */
/*                                  ERROR                                    */
/* ************************************************************************* */

/**
 * @ingroup scanner_reader
 * @brief Prints the read failure of @p path ("read error" with the errno
 *        message) and requalifies @p err to the POSIX read error.
 *
 * @param err The @c ERR_LIBC failure returned by the read.
 * @param path Name of the failing input, printed in the diagnostic
 *               (borrowed, read-only).
 * @return @c ERR_POSIX_READ (printed), always.
 */
t_error	on_read_error(t_error err, const char *path);

t_error	on_open_error(t_error err, const char *path);

#endif
