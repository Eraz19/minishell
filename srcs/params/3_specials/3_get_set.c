#include "libft.h"
#include "specials.h"

static t_error specials_get_positionnal(t_specials *specials, const char *name, char **dst)
{
	size_t	position;

	*dst = NULL;
	position = ft_atozu(name);	// TODO
	if (position >= specials->positional_count)
		return (ERR_NO);
	*dst = str_dup(specials->positional_params[position - 1]);
	if (!dst)
		return (ERR_LIBC);
	return (ERR_NO);
}

// @warning: *dst is owned by caller, he must free it if not NULL
t_error	specials_get_string(t_specials *specials, const char *name, char **dst)
{
	*dst = NULL;
	if (!name || name[0] == '\0')
		return (ERR_NO);
	else if (name[0] == '0' && name[1] == '\0')
		*dst = str_dup(specials->zero);
	else if (ft_isdigit(name[1]))
		return (specials_get_positionnal(specials, name, dst));
	else if (name[1] != '\0')
		return (ERR_VAR_NOT_FOUND);
	// else if (name[0] == '@' || name == '*')
	// 	*dst = // TODO: call expander ???;
	else if (name[0] == '#')
		*dst = ft_zutoa(specials->positional_count);	// TODO
	else if (name[0] == '$')
		*dst = ft_itoa(specials->pid);
	else if (name[0] == '!')
		*dst = ft_itoa(specials->last_bg_pid);
	else if (name[0] == '?')
		*dst = ft_itoa(specials->last_status);
	else
		return (ERR_VAR_NOT_FOUND);
	if (*dst == NULL)
		return (ERR_LIBC);
	return (ERR_NO);
}

t_error	specials_set(t_specials *specials, char name)
{

}
