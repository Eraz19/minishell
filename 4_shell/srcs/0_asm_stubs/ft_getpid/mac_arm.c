/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mac_arm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:40:11 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:40:12 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if defined(__APPLE__) && (defined(__aarch64__) || defined(__arm64__))
# include <sys/types.h>
# include <sys/syscall.h>

pid_t	ft_getpid(void)
{
	long	ret;

	__asm__ volatile (
		"mov x16, %1\n"
		"svc #0x80\n"
		"mov %0, x0\n"
		: "=r"(ret)
		: "r"((long)SYS_getpid)
		: "x0", "x16", "memory"
	);
	return ((pid_t)ret);
}

#endif
