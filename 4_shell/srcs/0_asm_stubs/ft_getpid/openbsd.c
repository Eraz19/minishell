#if defined(__OpenBSD__)
# include <unistd.h>

pid_t	ft_getpid(void)
{
	return ((pid_t)-1);
}

#endif
