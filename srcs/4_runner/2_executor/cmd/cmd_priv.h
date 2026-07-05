#ifndef CMD_PRIV_H
# define CMD_PRIV_H

# include "libft.h"
# include "builtins.h"
# include "functions.h"
# include <stdbool.h>

typedef enum e_cmd_type
{
	CMD_NONE,
	CMD_SPECIAL_BUILTIN,
	CMD_UNSPECIFIED,
	CMD_FUNCTION,
	CMD_BUILTIN,
	CMD_EXTERNAL
}	t_cmd_type;

// vector of t_expansion (t_expansion is a vector of t_string)
typedef t_vector	t_cmd_expansions;

typedef struct s_cmd_resolution
{
	t_cmd_type			type;
	t_cmd_expansions	expansions;
	char				*path;		// only if CMD_EXTERNAL (owned)
	t_builtin			builtin;	// only if builtin/intrinsic/special
	const t_function	*function;	// only if CMD_FUNCTION (borrowed)
	bool				is_declaration_utility;
}	t_cmd_resolution;

void	cmd_resolution_init(t_cmd_resolution *cmd_resolution);
void	cmd_resolution_free(t_cmd_resolution *cmd_resolution);
bool	cmd_name_is_special_builtin(const char *name, t_builtin *out_builtin);
bool	cmd_name_is_unspecified(const char *name);
bool	cmd_name_is_function(
			t_functions *functions,
			const char *name,
			const t_function **out_function);
bool	cmd_name_is_intrinsic_builtin(const char *name, t_builtin *out_builtin);
bool	cmd_name_is_regular_builtin(const char *name, t_builtin *out_builtin);

#endif
