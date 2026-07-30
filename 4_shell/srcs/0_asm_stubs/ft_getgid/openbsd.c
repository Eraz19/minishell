#if defined(__OpenBSD__)
# include <sys/types.h>

gid_t	ft_getgid(void)
{
	return ((gid_t)-1);
}

#endif
