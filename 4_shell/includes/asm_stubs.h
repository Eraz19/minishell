/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_stubs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:22:54 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:22:55 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_STUBS_H
# define ASM_STUBS_H

# include <unistd.h>

pid_t	ft_getpid(void);
pid_t	ft_getppid(void);
uid_t	ft_geteuid(void);
uid_t	ft_getuid(void);
uid_t	ft_getegid(void);
uid_t	ft_getgid(void);

#endif
