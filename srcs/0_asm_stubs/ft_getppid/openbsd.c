#if defined(__OpenBSD__)
# include <unistd.h>

pid_t	ft_getppid(void)
{
	return ((pid_t)-1);
}

#endif
