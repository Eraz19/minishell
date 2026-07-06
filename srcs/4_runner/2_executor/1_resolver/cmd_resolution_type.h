#ifndef CMD_RESOLUTION_TYPE_H
# define CMD_RESOLUTION_TYPE_H

# include "cmd_expansion.h"
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

typedef struct s_cmd_resolution
{
	t_cmd_type			type;
	t_cmd_expansions	expansions;
	char				*path;		// only if CMD_EXTERNAL (owned)
	t_builtin			builtin;	// only if builtin/intrinsic/special
	const t_function	*function;	// only if CMD_FUNCTION (borrowed)
	bool				is_declaration_utility;
}	t_cmd_resolution;

#endif
