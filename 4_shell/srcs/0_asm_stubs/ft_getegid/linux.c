/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linux.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:39:31 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:33:20 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if defined(__linux__)
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>

static int	ft_is_gid_field(const char *string, int index)
{
	return ((index == 0 || string[index - 1] == '\n')
		&& string[index] == 'G'
		&& string[index + 1] == 'i'
		&& string[index + 2] == 'd'
		&& string[index + 3] == ':');
}

static int	ft_skip_number(const char *string, int index)
{
	while (string[index] >= '0' && string[index] <= '9')
		index++;
	while (string[index] == ' ' || string[index] == '\t')
		index++;
	return (index);
}

static gid_t	ft_parse_egid(const char *string)
{
	unsigned long	egid;
	int				index;

	index = 0;
	while (string[index])
	{
		if (ft_is_gid_field(string, index))
		{
			index += 4;
			while (string[index] == ' ' || string[index] == '\t')
				index++;
			if (string[index] < '0' || string[index] > '9')
				return ((gid_t) - 1);
			index = ft_skip_number(string, index);
			if (string[index] < '0' || string[index] > '9')
				return ((gid_t) - 1);
			egid = 0;
			while (string[index] >= '0' && string[index] <= '9')
				egid = (egid * 10) + (unsigned long)(string[index++] - '0');
			return ((gid_t)egid);
		}
		index++;
	}
	return ((gid_t) - 1);
}

gid_t	ft_getegid(void)
{
	char	buf[4096];
	int		fd;
	ssize_t	nread;

	fd = open("/proc/self/status", O_RDONLY);
	if (fd < 0)
		return ((gid_t) - 1);
	nread = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	if (nread <= 0)
		return ((gid_t) - 1);
	buf[nread] = '\0';
	return (ft_parse_egid(buf));
}

#endif
