#if defined(__OpenBSD__)
# include <sys/types.h>

uid_t	ft_getuid(void)
{
	return ((uid_t)-1);
}

#endif
