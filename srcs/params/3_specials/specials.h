#ifndef SPECIALS_H
# define SPECIALS_H

# include "libft.h"
# include "error.h"
# include <stddef.h>
# include <sys/types.h>

// Payload of a node of a t_positionals_stack
typedef struct s_positionals
{
	char	**params;	// $@ / $* / $n
	size_t	count;		// $#
}	t_positionals;

// Linked list (alias of `t_node *`) containing t_positionals payloads
typedef t_list	t_positionals_stack;

typedef struct s_specials
{
	char				*zero;			// $0
	char				*source;		// (internal, can be NULL)
	t_positionals_stack	positionals;	// [$@ / $* / $n] + $# (top of stack)
	pid_t				pid;			// $$
	pid_t				last_bg_pid;	// $!
	int					last_status;	// $?
}	t_specials;

/*
Make `positionals` a distinct module bc it's enough complex to justify independent module

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

void	specials_init(t_specials *specials);

// @ret ERR_SHELL_NOT_FOUND / ERR_OPTION_INVALID
t_error	specials_load(
	t_specials *specials,
	int argc,
	char **argv,
	size_t options_count);
	
void	specials_free(t_specials *specials);

#endif
