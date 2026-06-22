#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>
# include <sys/stat.h>

typedef char	*t_file_path;

typedef union u_const_cast
{
	const char	*const_input;
	char		*input;
}	t_const_cast;

typedef struct stat	__stat_;

#endif
