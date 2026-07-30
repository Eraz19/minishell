#if defined(__APPLE__) && defined(__x86_64__)
# include <sys/types.h>
# include <sys/syscall.h>

pid_t	ft_getpid(void)
{
	long	ret;

	__asm__ volatile (
		"syscall\n"
		: "=a"(ret)
		: "a"(0x2000000L | (long)SYS_getpid)
		: "rcx", "r11", "memory"
	);
	return ((pid_t)ret);
}

#endif
