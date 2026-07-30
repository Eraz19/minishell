#if defined(__APPLE__) && defined(__x86_64__)
# include <sys/types.h>
# include <sys/syscall.h>

uid_t	ft_geteuid(void)
{
	long	ret;

	__asm__ volatile (
		"syscall\n"
		: "=a"(ret)
		: "a"(0x2000000L | (long)SYS_geteuid)
		: "rcx", "r11", "memory"
	);
	return ((uid_t)ret);
}

#endif
