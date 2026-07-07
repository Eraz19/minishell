#ifndef PATH_COMPS__H
# define PATH_COMPS__H

# include "libft.h"
# include "error.h"
# include "word_.h"

typedef t_vector	t_path_comps;

typedef struct s_path_comp
{
	bool		special;
	t_string	pattern;
}	t_path_comp;

void	path_comp_init(t_path_comp *comp);
void	path_comp_free(t_path_comp *comp);
void	path_comps_init(t_path_comps *comps);
void	path_comps_free(t_path_comps *comps);
t_error	path_comps_load(t_vector *comps, const t_word *src);

bool	path_comps_have_special(const t_path_comps *comps);
t_error	path_comps_get(t_path_comp *out, const t_path_comps *src, size_t i);

t_error	path_comp_push(t_path_comp *comp, t_word_item item);
t_error	path_comp_emit(t_path_comps *comps, t_path_comp *comp);
t_error	path_comps_push(t_path_comps *comps, t_path_comp comp);

bool	path_comp_is_special(const char *pattern);

#endif
