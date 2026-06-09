#ifndef UTILS_H
# define UTILS_H

# include "error.h"
# include <time.h>

time_t    get_now_unix_seconds(void);

// @ret ERR_ASSIGNMENT_MISSING_NAME / ERR_LIBC
t_error assignment_split(const char *src, char **dst_name, char **dst_value);

// @ret ERR_LIBC
t_error serialize(const char *src, char **dst);

// @ret ERR_INVALID_FORMAT / ERR_LIBC
t_error deserialize(const char *src, char **dst);

#endif
