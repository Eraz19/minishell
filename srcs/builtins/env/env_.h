#ifndef ENV__H
# define ENV__H

# include "error.h"
# include "libft.h"

/**
 * @struct s_env_args
 * @brief The name=value operands of one env invocation.
 *
 * @var s_env_args::assigns First name=value operand (borrowed view into
 *                          argv).
 * @var s_env_args::assign_count Number of consecutive name=value
 *                               operands starting at @c assigns.
 */
typedef struct s_env_args
{
	char	**assigns;
	size_t	assign_count;
}	t_env_args;

/**
 * @brief Reports whether two name=value strings (or bare names) carry
 *        the same name: both are compared up to their first @c = or
 *        end of string.
 *
 * @param a First entry (borrowed, read-only).
 * @param b Second entry (borrowed, read-only).
 * @return true when the names match.
 */
bool	env_same_name(const char *a, const char *b);

/**
 * @brief Writes one name=value entry and its newline to standard
 *        output.
 *
 * @param entry Entry to write (borrowed, read-only).
 * @return @c ERR_POSIX_WRITE or @c ERR_INTERRUPTED from the writer,
 *         @c ERR_NO on success.
 */
t_error	env_print_entry(const char *entry);

/**
 * @brief Writes the resulting environment to standard output, one
 *        name=value pair per line (POSIX "%s=%s\n").
 *
 * Every inherited entry is written in place, replaced by the last
 * name=value operand carrying its name when one exists; name=value
 * operands introducing a new name are then written in order (last
 * occurrence of a repeated name wins).
 *
 * @param envp Inherited environment, NULL-terminated; NULL for an
 *             empty inherited environment (env -i) (borrowed,
 *             read-only).
 * @param args name=value operands (borrowed, read-only).
 * @return @c ERR_POSIX_WRITE or @c ERR_INTERRUPTED from the writer,
 *         @c ERR_NO on success.
 */
t_error	env_print(char **envp, const t_env_args *args);

#endif
