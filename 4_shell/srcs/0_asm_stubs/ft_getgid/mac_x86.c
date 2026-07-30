#if defined(__APPLE__) && defined(__x86_64__)
# include <sys/types.h>
# include <sys/syscall.h>

gid_t	ft_getgid(void)
{
	long	ret;

	__asm__ volatile (
		"syscall\n"
		: "=a"(ret)
		: "a"(0x2000000L | (long)SYS_getgid)
		: "rcx", "r11", "memory"
	);
	return ((gid_t)ret);
}

#endif
