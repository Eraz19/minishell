#ifndef UTILS_H
# define UTILS_H

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

// home/user lookup reimplemented over /etc/passwd (getpwnam is forbidden).
// Returns a pointer to static storage (invalidated by the next call), or NULL
// when name is NULL, the file cannot be read, or no matching entry exists.
struct passwd	*ft_getpwnam(const char *name);

#endif
