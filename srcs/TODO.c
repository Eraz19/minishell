#include "error.h"
#include "expander_.h"
#include <stdbool.h>

/* ---------- TODO: shell ---------- */

t_error		shell_should_interrupt(bool *out)
{
	*out = true;
	return (error(ERR_NO));
}

/* ---------- TODO: expander ---------- */

t_error	path_name_expansion(t_expander *state)
{
	(void)state;
	return (error(ERR_NO));
}

// t_error	expander_expand_word(const t_token *word, t_vector *out)
// {
// 	(void)word;
// 	(void)out;
// 	return (error(ERR_NO));
// }

// out is a vector of t_buff
t_error	expander_expand_filename(const t_token *filename, t_vector *out)
{
	(void)filename;
	(void)out;
	return (error(ERR_NO));
}

t_error	expander_expand_heredoc_delim(const t_buff *heredoc_delim, t_buff *out)
{
	(void)heredoc_delim;
	(void)out;
	return (error(ERR_NO));
}

t_error	expander_expand_heredoc_body(const t_buff *heredoc_file_path)
{
	(void)heredoc_file_path;
	return (error(ERR_NO));
}

t_error	expander_expand_assignment(const t_token *assignment, t_buff *out)
{
	(void)assignment;
	(void)out;
	return (error(ERR_NO));
}
