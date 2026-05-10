#if defined(__linux__)
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>

static pid_t	ft_parse_pid(const char *string)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (string[i])
	{
		if (string[i] == 'P' && string[i + 1] == 'i'
			&& string[i + 2] == 'd' && string[i + 3] == ':')
		{
			i += 4;
			while (string[i] == ' ' || string[i] == '\t')
				i++;
			pid = 0;
			while (string[i] >= '0' && string[i] <= '9')
				pid = (pid * 10) + (string[i++] - '0');
			return (pid);
		}
		i++;
	}
	return ((pid_t)-1);
}

pid_t	ft_getpid(void)
{
	char	buf[512];
	int		fd;
	ssize_t	nread;

	fd = open("/proc/self/status", O_RDONLY);
	if (fd < 0)
		return ((pid_t)-1);
	nread = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	if (nread <= 0)
		return ((pid_t)-1);
	buf[nread] = '\0';
	return (ft_parse_pid(buf));
}

#endif
