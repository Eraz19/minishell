#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include "error.h"
# include <pwd.h>
# include <time.h>
# include "error.h"

time_t	get_now_unix_seconds(void);

bool	name_is_valid(const char *name);

// @ret ERR_ASSIGNMENT_MISSING_NAME / ERR_LIBC
t_error assignment_split(const char *src, char **dst_name, char **dst_value);

// @ret ERR_LIBC
t_error serialize(const char *src, char **dst);

// @ret ERR_INVALID_FORMAT / ERR_LIBC
t_error deserialize(const char *src, char **dst);

// @ret ERR_LIBC
t_error	deserialize_all(const char *src, t_vector *dst);

// home/user lookup reimplemented over /etc/passwd (getpwnam is forbidden).
// On success returns ERR_NO and sets *out_pw either to a pointer to static
// storage (invalidated by the next call) when a matching entry is found, or to
// NULL when name is NULL or no entry matches (not an error: the caller leaves
// the tilde literal). On a read failure returns ERR_LIBC, or ERR_INTERRUPTED if
// a signal interrupted the open; *out_pw is set to NULL in both cases.
// @ret ERR_INTERRUPTED / ERR_LIBC
t_error	ft_getpwnam(const char *name, struct passwd **out_pw);

#endif
