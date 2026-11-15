/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linux.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:40:37 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:37:09 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if defined(__linux__)
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>

static int	ft_is_uid_field(const char *string, int index)
{
	return ((index == 0 || string[index - 1] == '\n')
		&& string[index] == 'U'
		&& string[index + 1] == 'i'
		&& string[index + 2] == 'd'
		&& string[index + 3] == ':');
}

static uid_t	ft_parse_uid(const char *string)
{
	unsigned long	uid;
	int				index;

	index = 0;
	while (string[index])
	{
		if (ft_is_uid_field(string, index))
		{
			index += 4;
			while (string[index] == ' ' || string[index] == '\t')
				index++;
			if (string[index] < '0' || string[index] > '9')
				return ((uid_t) - 1);
			uid = 0;
			while (string[index] >= '0' && string[index] <= '9')
			{
				uid = (uid * 10)
					+ (unsigned long)(string[index] - '0');
				index++;
			}
			return ((uid_t)uid);
		}
		index++;
	}
	return ((uid_t) - 1);
}

uid_t	ft_getuid(void)
{
	char	buf[4096];
	int		fd;
	ssize_t	nread;

	fd = open("/proc/self/status", O_RDONLY);
	if (fd < 0)
		return ((uid_t) - 1);
	nread = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	if (nread <= 0)
		return ((uid_t) - 1);
	buf[nread] = '\0';
	return (ft_parse_uid(buf));
}

#endif
