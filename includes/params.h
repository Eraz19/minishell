#ifndef PARAMS_H
# define PARAMS_H

# include "variables.h"
# include "options.h"
# include "specials.h"
# include "positionals.h"
# include "functions.h"

typedef struct s_params
{
	void				*parent_shell;	// (internal)
	const char			*name;			// (internal)
	t_var_list			variables;		// $<var_name>
	t_option			options;		// $-
	t_specials			specials;		// $0 $$ $! $?
	t_positionals_stack	positionals;	// $@ $* $# $<n>
	t_fun_list			functions;		// (internal)
}	t_params;

/*
GENERAL:
- t_error params_get(const t_params *params, const char *name, char **dst):
	- renvoie toujours un `char *` mais il ne permet PAS d'accéder aux positional params
	- renvoie ce que fournissent les getters respectifs des modules `variables` ($<var>), `options` ($-) et `specials` ($0, $$, $!, $?).
- t_error params_set(t_params *params, const char *name, const char *value):
	- permet uniquement de set les valeurs de $? et $! ainsi que des variables
	- le module `params` étant agnostique de la logique qui drive la modification de ces champs, il les modifie "bêtement" quand on lui demande, ce sont les callers qui sont responsables de l'appeler au bon moment avec les bonnes valeurs, `params` n'est garant que de leur validité lors de l'initialisation.
- t_error params_set_option(t_params *params, t_option option, bool active):
	- permet de modifier la valeur des options (sauf -s, -i et -c qui ne peuvent pas être modifiées en cours d'exécution)

POSITIONAL PARAMS:
- t_error params_get_positionals(const t_params *params, t_positionals *dst):
	- renvoie le char ** et le size_t correspondants.
	- current_positionals est initialisé à la valeur de initial_positionals.
	- current_positionals est modifié lors de l'appel d'une fonction, puis restauré à la fin de celle-ci.
- t_error params_push_positionals(t_params *params, const t_positionals *src):
	- Ajoute les positionals passés en argument à la stack de positionals
	- Remplace la valeur actuelle de current_positionals par celle donnée en argument.
- t_error params_replace_positionals(t_params *params, t_positionals *src)
	- src will replace the top of the positionals stack (owned by specials module)
- t_error params_pop_positionals(t_params *params):
	- free les current_positionals et les remplace par ceux juste en dessous dans positionals_stack
	- Le premier élément de positionals_stack ne peut pas être pop car ce sont les positionals arguments donnés à l'invocation du shell
*/

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

void	params_init(t_params *params);
t_error	params_load(t_params *params, int argc, char **argv, char **envp);
void	params_free(t_params *params);

#endif
