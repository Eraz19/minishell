#include "path_matches_.h"

void	path_matches_init(t_path_matches *matches)
{
	vector_init(matches, sizeof(t_string), 0);
}

void	path_matches_free(t_path_matches *matches)
{
	vector_free(matches, string_free_void);
}
