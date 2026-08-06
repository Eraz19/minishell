/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mac_arm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:39:47 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:39:48 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if defined(__APPLE__) && (defined(__aarch64__) || defined(__arm64__))
# include <sys/types.h>
# include <sys/syscall.h>

uid_t	ft_geteuid(void)
{
	long	ret;

	__asm__ volatile (
		"mov x16, %1\n"
		"svc #0x80\n"
		"mov %0, x0\n"
		: "=r"(ret)
		: "r"((long)SYS_geteuid)
		: "x0", "x16", "memory"
	);
	return ((uid_t)ret);
}

#endif
