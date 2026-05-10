#if defined(__linux__)
# include <fcntl.h>
# include <unistd.h>

static int	ft_parse_ppid(const char *s)
{
	int	i;
	int	ppid;

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
	return (-1);
}

int	ft_getppid(void)
{
	char	buf[512];
	int		fd;
	int		ppid;
	ssize_t	nread;

	fd = open("/proc/self/status", O_RDONLY);
	if (fd < 0)
		return (-1);
	nread = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	if (nread <= 0)
		return (-1);
	buf[nread] = '\0';
	ppid = ft_parse_ppid(buf);
	return (ppid);
}

#endif
