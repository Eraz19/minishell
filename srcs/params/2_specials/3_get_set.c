#include "libft.h"
#include "specials.h"

t_error	specials_get(const t_specials *specials, char name, char **dst)
{
	*dst = NULL;
	if (name == '0')
		*dst = str_dup(specials->zero);
	else if (name == '$')
		*dst = ft_pidtoa(specials->pid);
	else if (name == '!')
	{
		if (specials->last_bg_pid == -1)
			return (ERR_NO);
		*dst = ft_pidtoa(specials->last_bg_pid);
	}
	else if (name == '?')
		*dst = ft_ltoa(specials->last_status);
	else
		return (ERR_VAR_NOT_FOUND);
	if (*dst == NULL)
		return (ERR_LIBC);
	return (ERR_NO);
}

void	specials_set_last_bg_pid(t_specials *specials, pid_t value)
{
	specials->last_bg_pid = value;
}

void	specials_set_last_status(t_specials *specials, int value)
{
	specials->last_status = value;
}
