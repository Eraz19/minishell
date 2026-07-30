#include "libft.h"
#include "specials.h"
#include <stdlib.h>

static t_error	specials_get_from_alloc(char *src, t_string *dst)
{
	t_error	err;

	if (!src)
		return (error_sys());
	if (!string_init(dst, 0, src, -1))
		err = error_sys();
	else
		err = error(ERR_NO);
	free(src);
	return (err);
}

t_error	specials_get(const t_specials *specials, char name, t_string *dst)
{
	if (name == '0')
	{
		if (!string_init(
			dst, 0, specials->zero.data, (ssize_t)specials->zero.len))
			return (error_sys());
	}
	else if (name == '$')
		return (specials_get_from_alloc(ft_pidtoa(specials->pid), dst));
	else if (name == '!')
	{
		if (specials->last_bg_pid == -1)
			return (error(ERR_NO));
		return (specials_get_from_alloc(ft_pidtoa(specials->last_bg_pid), dst));
	}
	else if (name == '?')
		return (specials_get_from_alloc(ft_ltoa(specials->last_status), dst));
	else
		return (error(ERR_VAR_NOT_FOUND));
	return (error(ERR_NO));
}

void	specials_set_last_bg_pid(t_specials *specials, pid_t value)
{
	specials->last_bg_pid = value;
}

void	specials_set_last_status(t_specials *specials, int value)
{
	specials->last_status = value;
}
