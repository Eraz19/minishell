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

static gid_t	ft_parse_gid(const char *string)
{
	unsigned long	gid;
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
				return ((gid_t)-1);
			gid = 0;
			while (string[index] >= '0' && string[index] <= '9')
			{
				gid = (gid * 10)
					+ (unsigned long)(string[index] - '0');
				index++;
			}
			return ((gid_t)gid);
		}
		index++;
	}
	return ((gid_t)-1);
}

gid_t	ft_getgid(void)
{
	char	buf[4096];
	int		fd;
	ssize_t	nread;

	fd = open("/proc/self/status", O_RDONLY);
	if (fd < 0)
		return ((gid_t)-1);
	nread = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	if (nread <= 0)
		return ((gid_t)-1);
	buf[nread] = '\0';
	return (ft_parse_gid(buf));
}

#endif
