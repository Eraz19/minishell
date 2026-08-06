/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mac_x86.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:39:49 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:39:50 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
