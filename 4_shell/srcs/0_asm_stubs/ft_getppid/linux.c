/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linux.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:40:23 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:40:24 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if defined(__linux__)
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>

static pid_t	ft_parse_ppid(const char *s)
{
	int		i;
	pid_t	ppid;

	i = 0;
	while (s[i])
	{
		if (s[i] == 'P' && s[i + 1] == 'P' && s[i + 2] == 'i'
			&& s[i + 3] == 'd' && s[i + 4] == ':')
		{
			i += 5;
			while (s[i] == ' ' || s[i] == '\t')
				i++;
			ppid = 0;
			while (s[i] >= '0' && s[i] <= '9')
				ppid = (ppid * 10) + (s[i++] - '0');
			return (ppid);
		}
		i++;
	}
	return ((pid_t)-1);
}

pid_t	ft_getppid(void)
{
	char	buf[512];
	int		fd;
	pid_t	ppid;
	ssize_t	nread;

	fd = open("/proc/self/status", O_RDONLY);
	if (fd < 0)
		return ((pid_t)-1);
	nread = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	if (nread <= 0)
		return ((pid_t)-1);
	buf[nread] = '\0';
	ppid = ft_parse_ppid(buf);
	return (ppid);
}

#endif
