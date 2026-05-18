#include "libft.h"
#include "specials.h"

t_error	specials_get(const t_specials *specials, char name, char **dst)
{
	*dst = NULL;
	if (name == '0')
		*dst = str_dup(specials->zero);
	else if (name == '$')
		*dst = ft_ltoa((long)specials->pid);
	else if (name == '!')
	{
		if (specials->last_bg_pid == -1)
			return (ERR_NO);
		*dst = ft_ltoa((long)specials->last_bg_pid);
	}
	else if (name == '?')
		*dst = ft_ltoa(specials->last_status);
	else
		return (ERR_VAR_NOT_FOUND);
	if (*dst == NULL)
		return (ERR_LIBC);
	return (ERR_NO);
}

t_error	specials_set(t_specials *specials, char name, long value)
{
	if (name == '!')
		specials->last_bg_pid = (pid_t)value;
	else if (name == '?')
		specials->last_status = value;
	else
		return (ERR_VAR_NOT_FOUND);
	return (ERR_NO);
}
