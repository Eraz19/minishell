#include "cmd_assignator.h"
#include "cmd_expansion.h"

/*
TODO: replace params_build_envp() by params_get_all_exported_variables() -> t_vector(<t_string name> + <t_string value>)
*/

/*
1. `expand` assignment values
2. check `readonly`
3. `CMD_NONE` / `CMD_SPECIAL_BUILTIN` / `CMD_FUNCTION` => commit assignments to variables
4. `CMD_BUILTIN` / `CMD_EXTERNAL`:
	- build `envp` from exported variables
	- add assignments to `envp`
*/

static inline t_error	cmd_expand_assignment(t_tokens *assignments, size_t index, char ***envp)
{

}

t_error	cmd_assign(t_cmd_type cmd_type, t_tokens *assignments, char ***envp)
{
	t_exp_flag			flags;
	size_t				i;
	t_token				*assignment;
	t_cmd_expansions	expansions;
	t_error				err;

	cmd_expansions_init(&expansions);
	flags = cmd_assignment_expansion_flags();
	err = error(ERR_NO);
	i = 0;
	while (i < assignments->len)
	{
		err = tokens_get(assignments, i, &assignment);
		if (err.type)
			return (err);
		expand_token(t_expansion *out, const t_token *src, t_exp_flag flags)
		i++;
	}
	return (err);
}
