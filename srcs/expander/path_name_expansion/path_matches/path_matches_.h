#ifndef PATH_MATCHES__H
# define PATH_MATCHES__H

# include "error.h"
# include "libft.h"
# include "path_comps_.h"

typedef t_vector	t_path_matches;

void	path_matches_init(t_path_matches *matches);
void	path_matches_free(t_path_matches *matches);

void	path_matches_sort(t_path_matches *matches);
t_error	path_matches_push(t_path_matches *matches, t_string *match);
t_error	add_path_comp(t_path_matches *out, t_path_comp *src, bool first);
t_error	path_matches_get(t_string **out, t_path_matches *matches, size_t i);
t_error	add_path_comp_lookup(t_path_matches *out, t_path_comp *src, bool first);

t_error	path_match_append(t_string *cand, const char *pattern);
t_error	add_lookup_dir_matching(
			t_path_matches *out,
			t_string *match,
			t_path_comp *comp,
			bool first);
#endif
