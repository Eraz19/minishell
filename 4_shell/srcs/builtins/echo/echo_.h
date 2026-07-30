#ifndef ECHO__H
# define ECHO__H

# include "libft.h"

/**
 * @brief Appends one operand of @c echo to the output line, decoding
 *        the XSI escape sequences (@c \\a @c \\b @c \\c @c \\f @c \\n
 *        @c \\r @c \\t @c \\v @c \\\\ @c \\0num) when @p escapes is on.
 *
 * An unknown escape sequence is kept as-is (backslash included), and a
 * trailing lone backslash is kept. On @c \\c the function sets @p stop
 * and returns: the caller shall discard every remaining operand, the
 * separators and the trailing newline.
 *
 * @param out Output line the operand is appended to (borrowed).
 * @param arg Operand to append (borrowed, read-only).
 * @param escapes Whether escape sequences are decoded (bash @c -e).
 * @param stop Set to true when @c \\c is met, untouched otherwise
 *             (borrowed).
 * @return false on allocation failure, true on success.
 */
bool	echo_append_arg(
			t_string *out,
			const char *arg,
			bool escapes,
			bool *stop);

#endif
