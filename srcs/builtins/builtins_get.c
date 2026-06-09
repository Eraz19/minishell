#include "builtins.h"
#include "builtins_priv.h"

#define BUILTINS_SPECIAL_COUNT		3	// TODO: 15
#define BUILTINS_NON_SPECIAL_COUNT	0	// TODO: 16

static inline const t_builtin	*builtins_get_specials(void)
{
	static const t_builtin	builtins[BUILTINS_SPECIAL_COUNT] =
	{
		// {"break", break},
		// {"colon", colon},
		// {"continue", continue},
		// {"dot", dot},
		// {"eval", eval},
		// {"exec", exec},
		// {"exit", exit},
		{"export", export},
		{"readonly", readonly},
		// {"return", return},
		// {"set", set},
		// {"shift", shift},
		// {"times", times},
		// {"trap", trap},
		{"unset", unset}
	};

	return (builtins);
}

static inline const t_builtin	*builtins_get_non_specials(void)
{
	static const t_builtin	builtins[BUILTINS_NON_SPECIAL_COUNT] =
	{
		// {"alias", alias},
		// {"bg", bg},
		// {"cd", cd},
		// {"command", command},
		// {"fc", fc},
		// {"fg", fg},
		// {"getopts", getopts},
		// {"hash", hash},
		// {"jobs", jobs},
		// {"kill", kill},
		// {"read", read},
		// {"type", type},
		// {"ulimit", ulimit},
		// {"umask", umask},
		// {"unalias", unalias},
		// {"wait", wait}
	};

	return (builtins);
}

t_builtin_function	builtins_get(const char *name, bool special)
{
	const t_builtin 	*builtins;
	size_t				i;
	size_t				count;

	if (special)
	{
		builtins = builtins_get_specials();
		count = BUILTINS_SPECIAL_COUNT;
	}
	else
	{
		builtins = builtins_get_non_specials();
		count = BUILTINS_NON_SPECIAL_COUNT;
	}
	i = 0;
	while (i < count)
	{
		if (str_cmp(name, builtins[i].name) == 0)
			return (builtins[i].function);
		i++;
	}
	return (NULL);
}
