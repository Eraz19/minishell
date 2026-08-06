/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freebsd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:39:28 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:41:10 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __FreeBSD__
# include <sys/types.h>
# include <sys/syscall.h>

gid_t	ft_getegid(void)
{
	long	ret;

# if defined(__x86_64__) || defined(__amd64__)
	__asm__ volatile (
		"syscall\n"
		: "=a"(ret)
		: "a"((long)SYS_getegid)
		: "rcx", "r11", "memory"
	);
	return ((gid_t)ret);
# elif defined(__aarch64__) || defined(__arm64__)
	register long	syscall_number __asm__("x8");
	register long	result __asm__("x0");

	syscall_number = (long)SYS_getegid;
	__asm__ volatile (
		"svc #0\n"
		: "=r"(result)
		: "r"(syscall_number)
		: "memory"
	);
	return ((gid_t)result);
# else
	return ((gid_t)-1);
# endif
}

#endif
