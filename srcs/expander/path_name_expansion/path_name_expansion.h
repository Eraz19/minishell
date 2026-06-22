#ifndef PATH_NAME_EXPANSION_H
# define PATH_NAME_EXPANSION_H

# include "expander_.h"

typedef struct s_path_name_expansion
{
	size_t	i;
	t_error	err;
	char	*word;
	bool	reached_EOW;
}	t_path_name_expansion;

t_error	path_name_expansion(t_expander *state);

#endif
