#include "libft.h"
#include "cmd_resolver_priv.h"
#include "error.h"

static inline bool	cmd_name_is_unspecified2(const char *cmd_name)
{
	return (str_cmp(cmd_name, "enum") == 0
		|| str_cmp(cmd_name, "float") == 0
		|| str_cmp(cmd_name, "help") == 0
		|| str_cmp(cmd_name, "history") == 0
		|| str_cmp(cmd_name, "hist") == 0
		|| str_cmp(cmd_name, "integer") == 0
		|| str_cmp(cmd_name, "let") == 0
		|| str_cmp(cmd_name, "local") == 0
		|| str_cmp(cmd_name, "login") == 0
		|| str_cmp(cmd_name, "logout") == 0
		|| str_cmp(cmd_name, "map") == 0
		|| str_cmp(cmd_name, "mapfile") == 0
		|| str_cmp(cmd_name, "nameref") == 0
		|| str_cmp(cmd_name, "popd") == 0
		|| str_cmp(cmd_name, "print") == 0
		|| str_cmp(cmd_name, "pushd") == 0
		|| str_cmp(cmd_name, "readarray") == 0
		|| str_cmp(cmd_name, "repeat") == 0
		|| str_cmp(cmd_name, "savehistory") == 0
		|| str_cmp(cmd_name, "source") == 0
		|| str_cmp(cmd_name, "shopt") == 0
		|| str_cmp(cmd_name, "stop") == 0
		|| str_cmp(cmd_name, "suspend") == 0
		|| str_cmp(cmd_name, "typeset") == 0
		|| str_cmp(cmd_name, "whence") == 0);
}

static inline bool	cmd_name_is_unspecified(const char *cmd_name)
{
	return (str_cmp(cmd_name, "caller") == 0
		|| str_cmp(cmd_name, "cap") == 0
		|| str_cmp(cmd_name, "chdir") == 0
		|| str_cmp(cmd_name, "clone") == 0
		|| str_cmp(cmd_name, "comparguments") == 0
		|| str_cmp(cmd_name, "compcall") == 0
		|| str_cmp(cmd_name, "compctl") == 0
		|| str_cmp(cmd_name, "compdescribe") == 0
		|| str_cmp(cmd_name, "compfiles") == 0
		|| str_cmp(cmd_name, "compgen") == 0
		|| str_cmp(cmd_name, "compgroups") == 0
		|| str_cmp(cmd_name, "complete") == 0
		|| str_cmp(cmd_name, "compound") == 0
		|| str_cmp(cmd_name, "compquote") == 0
		|| str_cmp(cmd_name, "comptags") == 0
		|| str_cmp(cmd_name, "comptry") == 0
		|| str_cmp(cmd_name, "compvalues") == 0
		|| str_cmp(cmd_name, "declare") == 0
		|| str_cmp(cmd_name, "dirs") == 0
		|| str_cmp(cmd_name, "disable") == 0
		|| str_cmp(cmd_name, "disown") == 0
		|| str_cmp(cmd_name, "dosh") == 0
		|| str_cmp(cmd_name, "echotc") == 0
		|| str_cmp(cmd_name, "echoti") == 0
		|| cmd_name_is_unspecified2(cmd_name));
}

void	cmd_warn_if_unspecified(const char *cmd_name)
{
	t_string	message;

	if (str_cmp(cmd_name, "alloc") == 0
		|| str_cmp(cmd_name, "autoload") == 0
		|| str_cmp(cmd_name, "bind") == 0
		|| str_cmp(cmd_name, "bindkey") == 0
		|| str_cmp(cmd_name, "builtin") == 0
		|| str_cmp(cmd_name, "bye") == 0
		|| cmd_name_is_unspecified(cmd_name))
	{
		(void)string_init(&message, 0, NULL, 0);
		if (string_append_format(&message,
				"POSIX 2.9.1.4: If the command name matches the name of a "
				"utility listed in [..., %s, ...], the results are unspecified",
				cmd_name))
		{
			print_unspecified_behaviour(
				message.data,
				"continue regular command resolution");
			string_free(&message);
		}
	}
}
